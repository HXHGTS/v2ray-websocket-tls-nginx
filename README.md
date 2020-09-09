# v2ray-websocket-tls-nginx

## 警告⚠：此技术仅限用于个人搭建游戏加速器使用！！！若用于其他违法目的，后果自负！！！

手动搭建v2ray服务器，并部署网页页面，支持cdn中转

一句话执行(CentOS7):
```

```

CDN套用方法请参看[CDN.md](/cdn.md)

### 安装前准备：

1.一个域名，与服务器ip做好dns解析

2.该域名必须提前申请SSL证书用于加密（后续考虑加入自动申请证书）

3.脚本仅支持CentOS7系统，vps必须为KVM架构

4.脚本执行需要root权限登录系统，AWS等特殊机型打开root权限方法[看这里](https://hxhgts.github.io/AWSECSRoot/)

5.请在服务器后台防火墙放行tcp443(https)端口
