﻿#include <stdio.h>
#include <stdlib.h>


FILE* config;
char uuid[40],sni[30];
int mode;

int main(){
    system("clear");
Menu:UI();
    system("clear");
    if (mode == 1) {
        install_v2ray();
        goto Menu;
    }
    else if (mode == 2) {
        system("systemctl stop v2ray");
        system("systemctl stop nginx");
        system("systemctl start v2ray");
        system("systemctl start nginx");
        goto Menu;
    }
    else if (mode == 3) {
        printf("服务器配置:\n");
        system("cat /usr/local/etc/v2ray/config.json");
        printf("\n");
        printf("客户端配置:\n");
        system("cat /usr/local/etc/v2ray/client.json");
        printf("\n");
        goto Menu;
    }
    else if (mode == 4) {
        system("cat /usr/local/etc/v2ray/config.json");
        goto Menu;
    }
    else if (mode == 5) {
        system("vi /usr/local/etc/v2ray/config.json");
        system("systemctl restart v2ray");
        system("systemctl restart nginx");
        goto Menu;
    }
    else if (mode == 6) {
        system("vi /usr/local/etc/v2ray/config.json");
        system("vi /usr/local/etc/v2ray/config.json");
        system("systemctl restart v2ray");
        system("systemctl restart nginx");
        goto Menu;
    }
    else if (mode == 7) {
        system("systemctl stop v2ray");
        system("systemctl stop nginx");
        goto Menu;
    }
    else {
        exit(0);
    }
    return 0;
}

int UI() {
    printf("-----------------------------------------------------------\n");
    printf("----------------------v2ray安装工具-----------------------\n");
    printf("-----------------------------------------------------------\n");
    printf("安装前请先去阿里云或腾讯云申请域名与域名对应的SSL证书，否则会导致安装失败！\n");
    printf("-----------------------------------------------------------\n");
    printf("----------------------当前Kernel版本-----------------------\n");
    system("uname -sr");
    printf("-----------------------------------------------------------\n");
    printf("1.安装v2ray\n2.运行v2ray\n3.显示配置\n4.修改v2ray配置\n5.修改nginx配置\n6.更新域名与SSL证书\n7.关闭v2ray\n0.退出\n");
    printf("-----------------------------------------------------------\n");
    printf("请输入:");
    scanf("%d", &mode);
    return 0;
}

int install_v2ray() {
    KernelUpdate();
    printf("请输入已绑定此服务器ip的域名:");
    scanf("%s", sni);
    system("setenforce 0");
    system("yum install -y curl unzip epel-release nginx");
    system("wget https://raw.githubusercontent.com/v2fly/fhs-install-v2ray/master/install-release.sh -O install-release.sh");
    system("chmod +x install-release.sh");
    system("bash install-release.sh");
    system("sleep 3");
    system("rm -rf install-release.sh");
    system("rm -rf TCPO.sh");
    system("rm -rf KernelUpdate.sh");
    system("echo \"------------------------------------------------------------------------------------\" >> /usr/local/etc/v2ray/certificate.crt");
    system("echo \"请将pem或cer或crt格式的证书用记事本打开并将内容粘贴至此处. . .\" > /usr/local/etc/v2ray/certificate.crt");
    system("echo \"英文输入法下按i开始编辑，结束编辑先按ESC再按:wq回车以保存\" >> /usr/local/etc/v2ray/certificate.crt");
    system("echo \"-----------------以上为使用说明，编辑时请先删除所有文字再开始编辑！-------------------\" >> /usr/local/etc/v2ray/certificate.crt");
    system("vi /usr/local/etc/v2ray/certificate.crt");
    system("echo \"------------------------------------------------------------------------------------\" >> /usr/local/etc/v2ray/private.key");
    system("echo \"请将key格式的私钥用记事本打开并将内容粘贴至此处. . .\" > /usr/local/etc/v2ray/private.key");
    system("echo \"英文输入法下按i开始编辑，结束编辑先按ESC再按:wq回车以保存\" >> /usr/local/etc/v2ray/private.key");
    system("echo \"-----------------以上为使用说明，编辑时请先删除所有文字再开始编辑！-------------------\" >> /usr/local/etc/v2ray/private.key");
    system("vi /usr/local/etc/v2ray/private.key");
    printf("正在生成配置文件. . .\n");
    system("curl https://raw.githubusercontent.com/HXHGTS/v2ray-websocket-tls-nginx/master/config.json.1 > /usr/local/etc/v2ray/config.json");
    printf("正在生成强密码. . .\n");
    system("uuidgen > /usr/local/etc/v2ray/uuid.conf");
    config = fopen("/usr/local/etc/v2ray/uuid.conf", "r");
    fscanf(config, "%s", uuid);
    fclose(config);
    config = fopen("/usr/local/etc/v2ray/config.json", "a");
    fprintf(config, "       \"id\": \"%s\"  \n", uuid);
    fprintf(config, "       \"alterId\": 64  \n");
    fclose(config);
    system("curl https://raw.githubusercontent.com/HXHGTS/v2ray-websocket-tls-nginx/master/config.json.2 >> /usr/local/etc/v2ray/config.json");
    printf("正在配置html网页. . .\n");
    system("curl https://raw.githubusercontent.com/HXHGTS/v2ray-websocket-tls-nginx/master/default.conf.1 > /etc/nginx/conf.d/default.conf");
    config = fopen("/etc/nginx/conf.d/default.conf", "a");
    fprintf(config, "    server_name %s;  \n", sni);
    fclose(config);
    system("curl https://raw.githubusercontent.com/HXHGTS/v2ray-websocket-tls-nginx/master/default.conf.2 >> /etc/nginx/conf.d/default.conf");
    system("curl https://raw.githubusercontent.com/HXHGTS/v2rayServer/master/html.zip > /usr/share/nginx/html/html.zip");
    system("unzip -o /usr/share/nginx/html/html.zip -d /usr/share/nginx/html");
    system("rm -f /usr/share/nginx/html/html.zip");
    printf("正在启动nginx并将nginx写入开机引导项. . .\n");
    system("systemctl enable nginx && systemctl start nginx");
    config = fopen("/usr/local/etc/v2ray/client.json", "w");
    fprintf(config, "  - {name: %s, server: %s, port: 443, type: vmess, uuid: %s, alterId: 64, cipher: auto, tls: true, network: ws, ws-path: /iso, ws-headers: {Host: %s}}", sni,sni,uuid,sni);
    fclose(config);
    printf("正在启动v2ray并将v2ray写入开机引导项. . .\n");
    system("systemctl enable v2ray");
    system("systemctl start v2ray");
    printf("v2ray部署完成！\n");
    printf("Clash配置:\n\n");
    system("cat /usr/local/etc/v2ray/client.json");
    printf("\n\n");
    return 0;
}

int KernelUpdate() {
    if ((fopen("KernelUpdate.sh", "r")) == NULL) {
        printf("正在升级新内核. . .\n");
        system("wget https://github.com/HXHGTS/TCPOptimization/raw/master/KernelUpdate.sh");
        system("chmod +x KernelUpdate.sh");
        printf("正在升级，将自动触发重启以应用配置. . .\n");
        system("bash KernelUpdate.sh");
    }
    else {
        system("wget https://github.com/HXHGTS/TCPOptimization/raw/master/TCPO.sh");
        system("chmod +x TCPO.sh");
        system("bash TCPO.sh");
    }
    return 0;
}
