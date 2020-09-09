### 套用CDN

1.申请Cloudflare账号，绑定域名

2.打开workers，新建

3.输入代码
```
addEventListener(
"fetch",event => {
let url=new URL(event.request.url);
url.hostname="*************";
let request=new Request(url,event.request);
event. respondWith(
fetch(request)
)
}
)
```

*************用服务器域名替换

4.修改一个好记的名称，比如***.***.workers.dev,填入v2ray的ws-headers中，并将ip改为cloudflare的可用ip
