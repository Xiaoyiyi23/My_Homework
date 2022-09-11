# -*- codeing = utf-8 -*-
# @Time : 2022/9/7 12:49
import socket
import time
import pickle
import pyDH
import hashlib
from Crypto.PublicKey import ECC
from Crypto.Signature import DSS
from Crypto.Hash import SHA256

ip = "127.0.0.1"
port1 = 8080  # 服务器端口
port2 = 8898

print("输入数字1：Bob向服务器上传椭圆曲线公钥")
mod = input("请输入：")

if int(mod) == 1:
    sk = socket.socket()
    sk.connect((ip, port1))

    # 生成IKB（Bob身份认证公钥）
    IKB = pyDH.DiffieHellman()
    # IKB = d1.gen_public_key()

    # 生成SPK-B（Bob预共享公钥）
    SPKB = pyDH.DiffieHellman()
    SPKB_pubkey = SPKB.gen_public_key()
    # SPKB = d2.gen_public_key()

    # 生成OPK-B（Bob一次性预共享公钥）
    OPKB = pyDH.DiffieHellman()
    # OPKB = d3.gen_public_key()

    # 读取BobKey（用以签名）
    f = open('BobKey.pem', 'rt')
    BobKey = ECC.import_key(f.read())
    # print("BobKey:", BobKey)

    # 生成：Bob的预共享公钥的签名
    signer = DSS.new(BobKey, 'fips-186-3')
    SPKB_pubkey = str(SPKB_pubkey)
    hasher1 = SHA256.new(SPKB_pubkey.encode())  # Hash对象，取内容摘要
    # hasher.update(message.encode()) # 换种方式使用也可以
    Sign_IKB_SPKB = signer.sign(hasher1)  # 用私钥对消息签名

    # print('签名内容：', Sign_IKB_SPKB)1

    # IKB = bytes(IKB, encoding="utf-8")

    """
    IKB = str(IKB)
    IKB = IKB.encode()
    SPKB = str(SPKB)
    SPKB = SPKB.encode()
    OPKB = str(OPKB)
    OPKB = OPKB.encode()
    """
    BobKey = str(BobKey)
    BobKey = str.encode(BobKey)

    sk.send(pickle.dumps(IKB))
    time.sleep(1)
    print("\nIKB已发送")

    sk.send(pickle.dumps(SPKB))
    time.sleep(1)
    print("SPKB已发送")

    sk.send(pickle.dumps(OPKB))
    time.sleep(1)
    print("OPKB已发送")

    sk.send(BobKey)
    time.sleep(1)

    sk.send(Sign_IKB_SPKB)
    print("签名已发送")
    sk.close()

sk = socket.socket()
# 把地址绑定到套接字
sk.bind(('127.0.0.1', 8787))
# 监听链接
sk.listen(5)

conn, addr = sk.accept()
print("正在接收Alice的信息\n")
r_IKA = conn.recv(1024)
r_EKA = conn.recv(1024)
r_OPKB = conn.recv(1024)
# r_AD = conn.recv(1024)

IKAs = pickle.loads(r_IKA)
EKAs = pickle.loads(r_EKA)
OPKBs = pickle.loads(r_OPKB)

IKA_pubkey = IKAs.gen_public_key()
IKB_pubkey = IKB.gen_public_key()
EKA_pubkey = EKAs.gen_public_key()
OPKB_pubkey = OPKBs.gen_public_key()
SPKB_pubkey = SPKB.gen_public_key()

# dh1 = DH(IKA_pubkey, SPKB_pubkey)

IKA_sharedkey = IKAs.gen_shared_key(SPKB_pubkey)
SPKB_sharedkey = SPKB.gen_shared_key(IKA_pubkey)
if IKA_sharedkey == SPKB_sharedkey:
    sharedkey_1 = IKA_sharedkey
    # print(sharedkey_1)

# dh2 = DH(EKA_pubkey, IKB_pubkey)

EKA_sharedkey = EKAs.gen_shared_key(IKB_pubkey)
IKB_sharedkey = IKB.gen_shared_key(EKA_pubkey)
if EKA_sharedkey == IKB_sharedkey:
    sharedkey_2 = EKA_sharedkey

# dh3 = DH(EKA_pubkey, SPKB_pubkey)

EKA_sharedkey = EKAs.gen_shared_key(SPKB_pubkey)
SPKB_sharedkey = SPKB.gen_shared_key(EKA_pubkey)
if EKA_sharedkey == SPKB_sharedkey:
    sharedkey_3 = EKA_sharedkey

# dh4 = DH(EKA_pubkey, OPKB_pubkey)

EKA_sharedkey = EKAs.gen_shared_key(OPKB_pubkey)
OPKB_sharedkey = OPKBs.gen_shared_key(EKA_pubkey)
if EKA_sharedkey == OPKB_sharedkey:
    sharedkey_4 = EKA_sharedkey

strs = sharedkey_1 + sharedkey_2 + sharedkey_3 + sharedkey_4
md = hashlib.md5()
md.update(strs.encode('utf-8'))
print("\n密钥SK已生成:", md.hexdigest())
