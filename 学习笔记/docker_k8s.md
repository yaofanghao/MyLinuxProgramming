<!--
 * @Author: yao fanghao
 * @Date: 2023-09-27 09:19:30
 * @LastEditTime: 2023-09-27 10:31:10
 * @LastEditors: yao fanghao
-->
# 参考资料
* https://kubernetes.io/zh/docs/home
* https://docs.docker.com/get-started/

# docker
* 模拟完全相同的本地开发环境
* https://docs.docker.com/engine/install/ubuntu/

## Docker 基本概念

* **镜像（Image）**：只读模板，包含运行应用所需的文件系统、依赖、配置
* **容器（Container）**：镜像的运行实例，可读写，轻量级
* **Dockerfile**：构建镜像的脚本
  ```dockerfile
  FROM ubuntu:22.04
  RUN apt-get update && apt-get install -y nginx
  COPY ./html /usr/share/nginx/html
  EXPOSE 80
  CMD ["nginx", "-g", "daemon off;"]
  ```

## Dockerfile 最佳实践

* 选择小型基础镜像（alpine）减少攻击面
* 合并 RUN 指令减少层数
* 使用 .dockerignore 排除无关文件
* 多阶段构建：第一阶段编译，第二阶段只拷贝产物
  ```dockerfile
  # 编译阶段
  FROM golang:1.20 AS builder
  COPY . .
  RUN go build -o app

  # 运行阶段（仅包含编译产物，不含编译工具链）
  FROM alpine:latest
  COPY --from=builder /app /app
  CMD ["/app"]
  ```

## Docker 常用命令

| 命令 | 说明 |
|------|------|
| docker build -t name . | 构建镜像 |
| docker run -d -p 8080:80 name | 运行容器（后台，端口映射） |
| docker ps -a | 查看所有容器（含已停止） |
| docker images | 查看镜像列表 |
| docker exec -it <id> /bin/bash | 进入运行中的容器 |
| docker logs <id> | 查看容器日志 |
| docker-compose up -d | 通过docker-compose.yml启动多容器 |

## Docker Compose

* 定义和运行多容器应用
  ```yaml
  version: '3'
  services:
    web:
      build: .
      ports:
        - "8080:80"
    db:
      image: postgres:15
      environment:
        POSTGRES_PASSWORD: secret
  ```

## 镜像分层原理

* 镜像由只读层（layer）堆叠而成
* 每层记录文件变更（增量）
* 容器运行时在镜像层上加可写层（容器层）
* 写时复制（Copy-on-Write）：修改文件时复制到容器层

# k8s
* 安装kubectl
```
curl -LO "https://dl.k8s.io/release/$(curl -L -s https://dl.k8s.io/release/stable.txt)/bin/linux/amd64/kubectl"
sudo install -o root -g root -m 0755 kubectl /usr/local/bin/kubectl
kubectl version --client  
```

## K8s 核心概念

* **Pod**：最小的调度单元，包含一个或多个容器，共享网络和存储
* **Deployment**：声明式管理 Pod 的副本数、滚动更新、回滚
* **Service**：提供稳定的网络入口，负载均衡到一组 Pod
  * ClusterIP：集群内部访问
  * NodePort：节点端口映射
  * LoadBalancer：云厂商负载均衡
* **ConfigMap / Secret**：配置管理和敏感信息管理
* **Namespace**：资源隔离

## K8s 常用命令

| 命令 | 说明 |
|------|------|
| kubectl get pods | 查看Pod列表 |
| kubectl apply -f deploy.yaml | 应用配置 |
| kubectl logs <pod-name> | 查看Pod日志 |
| kubectl exec -it <pod> -- /bin/bash | 进入Pod |
| kubectl port-forward <pod> 8080:80 | 端口转发到本地 |
| kubectl describe pod <pod> | 详细查看Pod状态 |

## K8s 示例 Deployment

```yaml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: nginx-deployment
spec:
  replicas: 3
  selector:
    matchLabels:
      app: nginx
  template:
    metadata:
      labels:
        app: nginx
    spec:
      containers:
      - name: nginx
        image: nginx:1.25
        ports:
        - containerPort: 80
```

## K8s 架构组件

* **API Server**：集群入口，RESTful API
* **etcd**：分布式键值存储，保存集群状态
* **Scheduler**：调度Pod到合适节点
* **Controller Manager**：维护集群期望状态（Deployment、ReplicaSet等）
* **Kubelet**：节点代理，管理Pod生命周期
* **Kube-proxy**：网络代理，实现Service转发规则

## K8s 网络模型

* **每个 Pod 拥有独立 IP**，Pod 间可直接通信（无需 NAT）
* **CNI（Container Network Interface）**：插件化网络方案

### 常见 CNI 插件

| 插件 | 特点 | 适用场景 |
|------|------|---------|
| Flannel | 简单，VXLAN/overlay 网络 | 小规模集群，网络要求不高 |
| Calico | 纯三层 BGP 路由，支持 NetworkPolicy | 大规模集群，性能要求高 |
| Cilium | 基于 eBPF，高性能，安全可观测 | 云原生、微服务、安全敏感 |
| Weave | 简单易用，自带 DNS | 快速搭建 |

### Service 类型与实现

* **ClusterIP**：通过 iptables/IPVS 做 DNAT，将请求转发到后端 Pod
* **NodePort**：在每个节点上开放端口，`nodeIP:NodePort` 访问
* **LoadBalancer**：云厂商提供外部负载均衡器，自动创建 NodePort
* **Ingress**：七层（HTTP/HTTPS）路由，支持域名/路径转发、TLS 终止

## Helm（K8s 包管理器）

* **Chart**：K8s 资源模板的打包格式
* **Release**：Chart 在集群中的一个部署实例
* **常用命令**

```shell
helm repo add bitnami https://charts.bitnami.com/bitnami
helm search repo nginx
helm install my-nginx bitnami/nginx --set replicaCount=3
helm upgrade my-nginx bitnami/nginx -f values.yaml
helm rollback my-nginx 1
helm list
helm uninstall my-nginx
```

## 存储

### 卷类型

| 类型 | 说明 |
|------|------|
| emptyDir | Pod 内共享，Pod 删除时数据清除 |
| hostPath | 宿主机目录挂载 |
| PersistentVolumeClaim（PVC） | 声明式存储请求 |
| ConfigMap / Secret | 配置注入 |
| NFS / Ceph / AWS EBS | 外部存储系统 |

### PV / PVC 生命周期

1. 管理员创建 PersistentVolume（PV）
2. 用户创建 PersistentVolumeClaim（PVC）声明需求（大小、访问模式）
3. K8s 将匹配的 PV 绑定到 PVC
4. Pod 使用 PVC 作为卷挂载
5. 删除 PVC 后，PV 根据回收策略（Retain/Recycle/Delete）处理

## 监控与日志

### Prometheus + Grafana

```yaml
# Prometheus 配置示例
scrape_configs:
  - job_name: 'kubernetes-pods'
    kubernetes_sd_configs:
      - role: pod
    relabel_configs:
      - source_labels: [__meta_kubernetes_pod_annotation_prometheus_io_scrape]
        action: keep
        regex: true
```

### 日志收集架构

```
Pod 日志 → Fluentd/Filebeat → Elasticsearch/Loki → Kibana/Grafana
```

* **Sidecar 模式**：每个 Pod 中运行日志采集容器
* **DaemonSet 模式**：每个节点运行一个日志采集 Pod

## K8s 安全

| 概念 | 说明 |
|------|------|
| RBAC | 基于角色的访问控制（Role / ClusterRole / RoleBinding） |
| ServiceAccount | Pod 的身份标识 |
| NetworkPolicy | 网络流量控制（入站/出站规则） |
| PodSecurityPolicy | Pod 安全策略（已废弃，PSA 替代） |
| Secret | 敏感信息存储（Base64 编码，建议用外部 KMS） |
| OPA/Gatekeeper | 策略引擎，准入控制 |

## K8s 调度

### 调度流程

1. **节点过滤（Predicates）**：排除不满足条件的节点（资源不足、端口冲突、污点容忍）
2. **节点打分（Priorities）**：对剩余节点打分（资源利用率、亲和性、taint toleration）
3. **绑定（Binding）**：选择最高分节点，将 Pod 绑定到该节点

### 调度策略

```yaml
# 节点选择
spec:
  nodeSelector:
    disk: ssd
  tolerations:
  - key: "gpu"
    operator: "Exists"
    effect: "NoSchedule"
  affinity:
    podAntiAffinity:
      requiredDuringSchedulingIgnoredDuringExecution:
      - labelSelector:
          matchLabels:
            app: myapp
        topologyKey: "kubernetes.io/hostname"
```

## 实战经验

### Pod 常见状态

| 状态 | 含义 |
|------|------|
| Pending | 等待调度到节点 |
| ContainerCreating | 拉取镜像、创建容器 |
| Running | 正常运行 |
| CrashLoopBackOff | 容器反复崩溃重启 |
| ImagePullBackOff | 镜像拉取失败 |
| OOMKilled | 内存超限被杀死 |
| Evicted | 节点资源不足被驱逐 |

### 故障排查命令

```shell
# 查看 Pod 事件
kubectl describe pod <pod>

# 查看容器日志
kubectl logs <pod> --tail=100 -f

# 查看上一崩溃的容器日志
kubectl logs <pod> --previous

# 进入容器排查
kubectl exec -it <pod> -- /bin/sh

# 查看节点资源
kubectl top node
kubectl top pod

# 端口转发到本地调试
kubectl port-forward svc/my-service 8080:80
```


