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

## 2. 启链

```bash
cd ~/output/

#允许升级
vim conf/xchain.yaml
   enableUpgrade: true

#关闭原来的链
pkill xchain
rm -rvf data/blockchain/

#创建链，后台启动链
xchain-cli createChain
nohup xchain --vm ixvm &

```

## 3. 创建测试用的角色

```bash
# 创建合约部署者 1234567890111111
xchain-cli account new --account 1234567890111111 --fee 1000
xchain-cli transfer --to XC1234567890111111@xuper --amount 10000000000000 --keys data/keys
xchain-cli account balance XC1234567890111111@xuper

# 创建基金会成员 1234567890222222
xchain-cli account new --account 1234567890222222 --fee 1000
xchain-cli transfer --to XC1234567890222222@xuper --amount 10000000000000 --keys data/keys
xchain-cli account balance XC1234567890222222@xuper

# 创建寺院 1234567890333333
xchain-cli account new --account 1234567890333333 --fee 1000
xchain-cli transfer --to XC1234567890333333@xuper --amount 10000000000000 --keys data/keys
xchain-cli account balance XC1234567890333333@xuper

# 创建法师 1234567890444444
xchain-cli account new --account 1234567890444444 --fee 1000
xchain-cli transfer --to XC1234567890444444@xuper --amount 10000000000000 --keys data/keys
xchain-cli account balance XC1234567890444444@xuper

# 创建用户 123456789055555
xchain-cli account new --account 123456789055555 --fee 1000
xchain-cli transfer --to 123456789055555@xuper --amount 10000000000000 --keys data/keys
xchain-cli account balance 123456789055555@xuper
```

## 4. 部署升级合约


```bash
xchain-cli wasm deploy --account XC1234567890111111@xuper --cname buddha --fee 5000000 --runtime c ../buddhaContract/buddha/buddha.wasm

xchain-cli wasm upgrade --account XC1234567890111111@xuper --cname buddha --fee 5000000 ../buddhaContract/buddha/buddha.wasm

xchain-cli wasm invoke --fee 1000000 buddha --method is_deployer --account XC1234567890111111@xuper
```

## 5. 流程测试

### 5.1 申请成为基金会成员

```bash
xchain-cli wasm invoke --fee 1000000 buddha --method apply_founder -a '{"desc":"apply to be founder"}' --account XC1234567890222222@xuper --amount 100000

xchain-cli wasm invoke --fee 1000000 buddha --method approve_founder -a '{"id":"XC1234567890222222@xuper"}' --account XC1234567890111111@xuper

xchain-cli wasm invoke --fee 1000000 buddha --method recusal_founder -a '{"id":"XC1234567890222222@xuper"}' --account XC1234567890111111@xuper

xchain-cli wasm invoke --fee 1000000 buddha --method is_founder --account XC1234567890222222@xuper

xchain-cli wasm invoke --fee 1000000 buddha --method list_founder --account XC1234567890222222@xuper
```

### 5.2 申请成为寺院

```bash
xchain-cli wasm invoke --fee 1000000 buddha --method apply_temple -a '{"unit":"佛山顶观音寺", "creditcode":"F110300007", "address":"浙江丽水佛顶山", "deedplaceproof":"xxxxx"}' --account XC1234567890333333@xuper

xchain-cli wasm invoke --fee 1000000 buddha --method approve_temple -a '{"id":"XC1234567890333333@xuper"}' --account XC1234567890222222@xuper

xchain-cli wasm invoke --fee 1000000 buddha --method recusal_temple -a '{"id":"XC1234567890333333@xuper"}' --account XC1234567890222222@xuper

xchain-cli wasm invoke --fee 1000000 buddha --method is_temple --account XC1234567890333333@xuper

xchain-cli wasm invoke --fee 1000000 buddha --method list_temple --account XC1234567890222222@xuper

```

### 5.3 申请成为法师

```bash
xchain-cli wasm invoke --fee 1000000 buddha --method apply_master -a '{"creditcode":"fashi123456"}' --account XC1234567890444444@xuper

xchain-cli wasm invoke --fee 1000000 buddha --method approve_master -a '{"id":"XC1234567890444444@xuper"}' --account XC1234567890222222@xuper

xchain-cli wasm invoke --fee 1000000 buddha --method recusal_master -a '{"id":"XC1234567890444444@xuper"}' --account XC1234567890222222@xuper

xchain-cli wasm invoke --fee 1000000 buddha --method is_master --account XC1234567890444444@xuper

xchain-cli wasm invoke --fee 1000000 buddha --method list_master --account XC1234567890222222@xuper

```

### 5.4 法师申请加入寺院

```bash
xchain-cli wasm invoke --fee 1000000 buddha --method apply_join_temple -a '{"templeid":"XC1234567890333333@xuper"}' --account XC1234567890444444@xuper

xchain-cli wasm invoke --fee 1000000 buddha --method approve_join_temple -a '{"templeid":"XC1234567890333333@xuper","masterid":"XC1234567890444444@xuper"}' --account XC1234567890222222@xuper

xchain-cli wasm invoke --fee 1000000 buddha --method recusal_join_temple -a '{"templeid":"XC1234567890333333@xuper","masterid":"XC1234567890444444@xuper"}' --account XC1234567890222222@xuper

xchain-cli wasm invoke --fee 1000000 buddha --method is_in_temple -a '{"templeid":"XC1234567890333333@xuper"}' --account XC1234567890444444@xuper

xchain-cli wasm invoke --fee 1000000 buddha --method list_temple_master -a '{"templeid":"XC1234567890333333@xuper"}' --account XC1234567890222222@xuper

xchain-cli wasm invoke --fee 1000000 buddha --method list_temple_master --account XC1234567890333333@xuper

```

### 5.5 添加删除修改善举

```bash
xchain-cli wasm invoke --fee 1000000 buddha --method add_kinddeed -a '{"id":"1", "name":"kd1", "lasttime":"xxxxxx", "detail":"[{\"sequence\":\"1\", \"hash\":\"xxxxxx\"},{\"sequence\":\"2\", \"hash\":\"yyyyyy\"}]", "spec":"[{\"sequence\":\"1\", \"desc\":\"aaaaaa\", \"price\":\"10\"},{\"sequence\":\"2\", \"desc\":\"bbbbbb\", \"price\":\"10\"}]" }' --account XC1234567890444444@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method delete_kinddeed -a '{"id":"1"}' --account XC1234567890444444@xuper

xchain-cli wasm invoke --fee 1000000 buddha --method update_kinddeed -a '{"id":"1", "name":"kd1", "lasttime":"xxxxxx", "detail":[{"sequence":"1", "hash":"xxxxxx"},{"sequence":"2", "hash":"yyyyyy"}], "spec":[{"sequence":"1", "desc":"aaaaaa", "price":"10"},{"sequence":"2", "desc":"bbbbbb", "price":"10"}] }' --account XC1234567890444444@xuper

xchain-cli wasm invoke --fee 1000000 buddha --method find_kinddeed -a '{"id":"1"}' --account XC1234567890222222@xuper

xchain-cli wasm invoke --fee 1000000 buddha --method list_kinddeed --account XC1234567890222222@xuper

```

### 5.6 申请善举上架下架

```bash
xchain-cli wasm invoke --fee 1000000 buddha --method apply_online_kinddeed -a '{"id":"1"}' --account XC1234567890333333@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method approve_online_kinddeed -a '{"id":"1"}' --account XC1234567890222222@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method find_kinddeed -a '{"id":"1"}' --account XC1234567890222222@xuper

xchain-cli wasm invoke --fee 1000000 buddha --method apply_offline_kinddeed -a '{"id":"1"}' --account XC1234567890333333@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method approve_offline_kinddeed -a '{"id":"1"}' --account XC1234567890222222@xuper
```

### 5.7 会员祈求善举

```bash
xchain-cli account balance XC1234567890444444@xuper

xchain-cli wasm invoke --fee 1000000 buddha --method pray_kinddeed -a '{"id": "1","suborders":"[{\"id\":\"1\",\"kdid\":\"1\",\"count\":\"1\"},{\"id\":\"2\",\"kdid\":\"1\",\"count\":\"2\"}]","timestamp":"11111"}' --account XC1234567890444444@xuper --amount 30

xchain-cli wasm invoke --fee 1000000 buddha --method find_pray_kinddeed -a '{"id": "1"}' --account XC1234567890444444@xuper 

xchain-cli wasm invoke --fee 1000000 buddha --method list_order --account XC1234567890222222@xuper

```

### 5.8 基金会成员授权法师或寺院上传的善举凭证

```bash
xchain-cli account balance XC1234567890333333@xuper

xchain-cli wasm invoke --fee 1000000 buddha --method upload_kinddeed_proof -a '{"orderid":"1", "proof":"xxxxx", "timestamp":"xxxxxx"}' --account XC1234567890333333@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method approve_kinddeed_proof -a '{"orderid":"1"}' --account XC1234567890222222@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method refuse_kinddeed_proof -a '{"orderid":"1"}' --account XC1234567890222222@xuper

xchain-cli wasm invoke --fee 1000000 buddha --method list_kinddeed_proof --account XC1234567890222222@xuper

```

## 6. 其他接口测试

```bash
xchain-cli wasm invoke --fee 1000000 buddha --method find_kinddeed -a '{"id":"1"}' --account XC1234567890222222@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method find_pray_kinddeed -a '{"id": "1"}' --account XC1234567890444444@xuper 

xchain-cli transfer --to gbRjavZajSVuv6oKRbBqH9RaNCsjhetbr --amount 1000000 --keys data/keys

xchain-cli wasm invoke --fee 1000 buddha --method find_pray_kinddeed -a '{"id": "1"}' --keys data/testuser

```
