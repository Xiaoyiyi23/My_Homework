# -*- codeing = utf-8 -*-
# @Time : 2022/9/7 12:49

import socket
import time
import pickle
import hashlib
import pyDH
from Crypto.PublicKey import ECC
from Crypto.Signature import DSS
from Crypto.Hash import SHA256

ip = "127.0.0.1"
port1 = 8080  # 服务器端口
port2 = 8898

print("输入数字1：Alice向服务器请求Bob的椭圆曲线公钥信息")
mod = input("请输入：")

if int(mod) == 1:
    sk = socket.socket()
    sk.connect((ip, port1))

    print("\nAlice已向服务器发起Bob公钥信息的请求")
    print("Alice正在下载Bob的全部公钥信息")

    command = b'get_Bob_ECC'
    sk.send(command)

    IKB = sk.recv(1024)
    # IKBs = IKB[0]
    # print(pickle.loads(IKB))
    IKBs = pickle.loads(IKB)
    # print(IKBs)

    SPKB = sk.recv(1024)
    # SPKBs = SPKB[0]
    # SPKB_byte = pickle.dumps(SPKB)
    SPKBs = pickle.loads(SPKB)

    OPKB = sk.recv(1024)
    # OPKB_byte = pickle.dumps(OPKB)
    OPKBs = pickle.loads(OPKB)

    BobKey = sk.recv(1024)
    Sign_IKB_SPKB = sk.recv(1024)
    # Sign_IKB_SPKB = Sign_IKB_SPKB.decode()

    # print("IKB:", IKBs)
    # print("SPKB:", SPKBs)
    # print("OPKB:", OPKBs)
    # print("Sign_IKB_SPKB:", Sign_IKB_SPKB)
    print("Bob的公钥信息已全部下载完成")

    print("现在正在进行验签")
    # 验证签名

    # 读取BobKey（用以验签）
    f = open('BobKey.pem', 'rt')
    BobKey1 = ECC.import_key(f.read())
    # print("BobKey:", BobKey)

    SPKB_pubkey = SPKBs.gen_public_key()
    SPKB1 = str(SPKB_pubkey)
    verifer = DSS.new(BobKey1.public_key(), 'fips-186-3')  # 使用公钥创建校验对象
    hasher2 = SHA256.new(SPKB1.encode())  # 对收到的消息文本提取摘要
    # hasher2 = bytearray(Sign_IKB_SPKB)

    # SPKB = str(SPKB)
    # hasher1 = SHA256.new(SPKB.encode())  # Hash对象，取内容摘要

    # print("签名功能还有问题，暂且忽略")
    # print("签名功能已修复")
    try:
        verifer.verify(hasher2, Sign_IKB_SPKB)  # 校验摘要（本来的样子）和收到并解密的签名是否一致
        print("签名有效")
    except (ValueError, TypeError):
        print("签名无效")

    EKAs = pyDH.DiffieHellman()
    EKA_pubkey = EKAs.gen_public_key()

    IKAs = pyDH.DiffieHellman()
    IKA_pubkey = IKAs.gen_public_key()

    # SPKB_pubkey = SPKB_pubkey.decode()

    IKB_pubkey = IKBs.gen_public_key()
    OPKB_pubkey = OPKBs.gen_public_key()

    """
    IKB_pubkey = IKBs.gen_public_key()
    IKB = IKB_pubkey.decode()

    
    OPKB_pubkey = OPKBs.gen_public_key()
    OPKB = OPKB_pubkey.decode()
    
    SPKB = int.from_bytes(SPKB, byteorder='little')
    IKB = int.from_bytes(IKB, byteorder='little')
    OPKB = int.from_bytes(OPKB, byteorder='little')
    
    SPKB = int(SPKB)
    IKB = int(IKB)
    OPKB = int(OPKB)
    """
    # print(IKA)
    # print(SPKB)

    # dh1 = DH(IKA_pubkey, SPKB_pubkey)

    IKA_sharedkey = IKAs.gen_shared_key(SPKB_pubkey)
    SPKB_sharedkey = SPKBs.gen_shared_key(IKA_pubkey)
    if IKA_sharedkey == SPKB_sharedkey:
        sharedkey_1 = IKA_sharedkey
        # print(sharedkey_1)

    # dh2 = DH(EKA_pubkey, IKB_pubkey)

    EKA_sharedkey = EKAs.gen_shared_key(IKB_pubkey)
    IKB_sharedkey = IKBs.gen_shared_key(EKA_pubkey)
    if EKA_sharedkey == IKB_sharedkey:
        sharedkey_2 = EKA_sharedkey

    # dh3 = DH(EKA_pubkey, SPKB_pubkey)

    EKA_sharedkey = EKAs.gen_shared_key(SPKB_pubkey)
    SPKB_sharedkey = SPKBs.gen_shared_key(EKA_pubkey)
    if EKA_sharedkey == SPKB_sharedkey:
        sharedkey_3 = EKA_sharedkey

    # dh4 = DH(EKA_pubkey, OPKB_pubkey)

    EKA_sharedkey = EKAs.gen_shared_key(OPKB_pubkey)
    OPKB_sharedkey = OPKBs.gen_shared_key(EKA_pubkey)
    if EKA_sharedkey == OPKB_sharedkey:
        sharedkey_4 = EKA_sharedkey

    # print(type(sharedkey_1))

    # print("\nshare key1:", sharedkey_1)
    # print("share key2:", sharedkey_2)
    # print("share key3:", sharedkey_3)
    # print("share key4:", sharedkey_4)

    """
    dh1 = str(dh1)
    dh2 = str(dh2)
    dh3 = str(dh3)
    dh4 = str(dh4)
    """

    strs = sharedkey_1 + sharedkey_2 + sharedkey_3 + sharedkey_4
    # SK = hash(strs)
    md = hashlib.md5()
    md.update(strs.encode('utf-8'))
    print("\n密钥SK已生成:", md.hexdigest())

    IKA = pickle.dumps(IKAs)
    EKA = pickle.dumps(EKAs)
    AD = str(IKA) + str(IKB)
    sk.close()

sk = socket.socket()
sk.connect(('127.0.0.1', 8787))

sk.send(IKA)
time.sleep(1)
print("\nIKA已发送")

sk.send(EKA)
time.sleep(1)
print("EKA已发送")

sk.send(OPKB)
time.sleep(1)
print("OPKB已发送")

# sk.send(AD)
# print("AD已发送")
