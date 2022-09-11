# -*- codeing = utf-8 -*-
# @Time : 2022/9/7 12:49
import socket

# 创建服务器端套接字
import time

sk = socket.socket()

# 把地址绑定到套接字
sk.bind(('127.0.0.1', 8080))

# 监听链接
sk.listen(5)

print("\n-----服务器日志系统-----")

while True:
    # 接受Bob的公钥信息
    conn, addr = sk.accept()
    print("Bob连接中...")
    print("Bob已连接...\n")
    print("正在接收Bob的全部公钥信息\n")

    r_IKB = conn.recv(1024)
    # IKB = pickle.loads(r_IKB)
    # r_IKB = pickle.dumps(r_IKB)

    r_SPKB = conn.recv(1024)
    # SPKB = pickle.loads(r_SPKB)
    # r_SPKB = pickle.dumps(SPKB)
    # r_SPKB = pickle.dumps(r_SPKB)

    r_OPKB = conn.recv(1024)
    #OPKB = pickle.loads(r_OPKB)
    #r_OPKB = pickle.dumps(OPKB)
    # r_OPKB = pickle.dumps(r_OPKB)

    r_BobKey = conn.recv(1024)
    r_Sign_IKB_SPKB = conn.recv(1024)

    print("IKB:", r_IKB)
    print("SPKB:", r_SPKB)
    print("OPKB:", r_OPKB)
    print("Sign_IKB_SPKB:", r_Sign_IKB_SPKB)

    conn.close()
    sk.close()

    sk = socket.socket()
    # 把地址绑定到套接字
    sk.bind(('127.0.0.1', 8080))
    # 监听链接
    sk.listen(5)

    # 接受Alice的请求
    conn, addr = sk.accept()
    command = conn.recv(1024)
    print("\nAlice连接中...")
    print("Alice已连接...\n")
    if command == b'get_Bob_ECC':
        # 向Alice发送Bob的ECC公钥信息
        print("Alice正在下载Bob的全部公钥信息")
        conn.send(r_IKB)
        time.sleep(1)
        # print("\nIKB已发送")

        conn.send(r_SPKB)
        time.sleep(1)
        # print("SPKB已发送")

        conn.send(r_OPKB)
        time.sleep(1)
        # print("OPKB已发送")

        conn.send(r_BobKey)
        time.sleep(1)

        conn.send(r_Sign_IKB_SPKB)
        # print("签名已发送")

        print("\nAlice已下载完成BOb的全部公钥信息")
