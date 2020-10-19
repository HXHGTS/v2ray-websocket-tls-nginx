#!/bin/bash
VMESSCODE=$(base64 -w 0 << EOF
    {
      "v": "2",
      "ps": "ibmyes",
      "add": "",
##服务器地址
      "port": "443",
      "id": "",
##uuid
      "aid": "2",
      "net": "ws",
      "type": "none",
      "host": "",
##伪装域名
      "path": "iso",
      "tls": "tls"
    }
EOF
    )
echo "VMESS配置链接："
echo vmess://${VMESSCODE}
exit 0
