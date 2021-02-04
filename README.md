# buddhaContract

## 1. 编译

```bash
#生成协议源文件
cd ~/buddhaContract/src/
protoc --cpp_out=. buddha.proto

cd ..
xdev build
```
> protobuf 版本注意只能使用 3.7.1， fuck， 坑。

## 2. 启链，创建测试用的角色，部署升级合约

### 2.1 启链

```bash
cd ~/output/

#关闭原来的链
pkill xchain
rm -rvf data/blockchain/

#运行升级
vim conf/xchain.yaml
   enableUpgrade: true

#创建链，后台启动链
xchain-cli createChain
nohup xchain --vm ixvm &
```

### 2.2 创建测试用的角色

```bash
# 创建合约部署者 1234567890111111
xchain-cli account new --account 1234567890111111 --fee 1000
xchain-cli transfer --to XC1234567890111111@xuper --amount 10000000000000 --keys data/keys

# 创建基金会成员 1234567890222222
xchain-cli account new --account 1234567890222222 --fee 1000
xchain-cli transfer --to XC1234567890222222@xuper --amount 10000000000000 --keys data/keys

# 创建法师 1234567890333333
xchain-cli account new --account 1234567890333333 --fee 1000
xchain-cli transfer --to XC1234567890333333@xuper --amount 10000000000000 --keys data/keys

# 创建用户 123456789044444
xchain-cli account new --account 123456789044444 --fee 1000
xchain-cli transfer --to XC123456789044444@xuper --amount 10000000000000 --keys data/keys
```

### 2.3 部署升级合约

```bash
xchain-cli wasm deploy --account XC1234567890111111@xuper --cname buddha --fee 5000000 --runtime c ../buddhaContract/buddha/buddha.wasm

xchain-cli wasm upgrade --account XC1234567890111111@xuper --cname buddha --fee 5000000 ../buddhaContract/buddha/buddha.wasm
```

## 3. 流程测试

### 3.1 申请成为基金会成员

```bash
xchain-cli wasm invoke --fee 1000000 buddha --method apply_founder -a '{"desc":"1234567890222222 apply to be founder"}' --account 1234567890222222@xuper --amount 100000

xchain-cli wasm invoke --fee 1000000 buddha --method approve_founder -a '{"name":"1234567890222222@xuper"}' --account 1234567890111111@xuper

xchain-cli wasm invoke --fee 1000000 buddha --method recusal_founder -a '{"name":"1234567890222222@xuper"}' --account 1234567890111111@xuper
```

### 3.2 申请成为法师或寺院

```bash
xchain-cli wasm invoke --fee 1000000 buddha --method apply_master -a '{"desc":"1234567890333333 apply to be master"}' --account 1234567890333333@xuper

xchain-cli wasm invoke --fee 1000000 buddha --method approve_master -a '{"name":"1234567890333333@xuper"}' --account 1234567890222222@xuper

xchain-cli wasm invoke --fee 1000000 buddha --method recusal_master -a '{"name":"1234567890333333@xuper"}' --account 1234567890222222@xuper
```

### 3.3 申请善举上架下架

#### 3.3.1 添加删除修改善举

```bash
xchain-cli wasm invoke --fee 1000000 buddha --method add_kinddeed -a '{"id":"1", "name":"kd1", "desc":"kd1", "price":"10.000", "count":"100", "lasttime":"xxxxxx" }' --account 1234567890333333@xuper

xchain-cli wasm invoke --fee 1000000 buddha --method delete_kinddeed -a '{"id":"1"}' --account 1234567890333333@xuper

xchain-cli wasm invoke --fee 1000000 buddha --method update_kinddeed -a '{"id":"1", "name":"kd111", "desc":"kd111", "price":"100.000", "count":"1000", "lasttime":"yyyyy" }' --account 1234567890333333@xuper
```

#### 3.3.2 申请善举上架下架

```bash
xchain-cli wasm invoke --fee 1000000 buddha --method apply_online_kinddeed -a '{"id":"1"}' --account 1234567890333333@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method apply_offline_kinddeed -a '{"id":"1"}' --account 1234567890333333@xuper

xchain-cli wasm invoke --fee 1000000 buddha --method approve_offline_kinddeed -a '{"id":"1"}' --account 1234567890222222@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method approve_offline_kinddeed -a '{"id":"1"}' --account 1234567890222222@xuper
```

### 3.4 用户祈求善举

```bash
xchain-cli wasm invoke --fee 1000000 buddha --method pray_kinddeed -a '{"orderid":"1", "proof":"xxxxx", "timestamp":"xxxxxx"}' --account 1234567890444444@xuper
```

### 3.5 基金会成员授权法师或寺院上传的善举凭证

```bash
xchain-cli wasm invoke --fee 1000000 buddha --method upload_kinddeed_proof -a '{"orderid":"1", "proof":"xxxxx", "timestamp":"xxxxxx"}' --account 1234567890333333@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method approve_kinddeed_proof -a '{"orderid":"1"' --account 1234567890333333@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method refuse_kinddeed_proof -a '{"orderid":"1"' --account 1234567890333333@xuper
```


```bash
xchain-cli wasm invoke --fee 1000000 buddha --method find_kinddeed -a '{"id":"1"}' --account XC1234567890111111@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method add_kinddeed -a '{"id": "1", "name":"prodname","desc":"proddesc","price":"5", "count":"6","lasttime":"123456"}' --account XC1234567890111111@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method update_kinddeed -a '{"id": "1", "name":"prodname","desc":"proddesc","price":"5", "count":"6","lasttime":"123456"}' --account XC1234567890111111@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method del_kinddeed -a '{"id": "1"}'  --account XC1234567890111111@xuper

xchain-cli account balance XC1234567890111111@xuper
xchain-cli account balance XC1234567890222222@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method pray_kinddeed -a '{"id": "1","suborders":"[{\"id\":\"1\",\"kdid\":\"1\",\"count\":\"1\"},{\"id\":\"1\",\"kdid\":\"1\",\"count\":\"2\"}]","amount":"30","timestamp":"11111"}' --account XC1234567890222222@xuper

xchain-cli wasm invoke --fee 1000000 buddha --method find_kinddeed -a '{"id":"1"}' --account XC1234567890222222@xuper

```
