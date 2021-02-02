# buddhaContract
buddhacontract


# 测试主键是否起作用

```bash
#创建合约账户
xchain-cli account new --account 1234567890111111 --fee 1000
xchain-cli transfer --to XC1234567890111111@xuper --amount 10000000000000 --keys data/keys

xchain-cli account new --account 1234567890222222 --fee 1000
xchain-cli transfer --to XC1234567890222222@xuper --amount 10000000000000 --keys data/keys

```


> protobuf 版本注意只能使用 3.7.1， fuck， 坑。

```bash
#生成协议源文件
cd src/
protoc --cpp_out=. buddha.proto

cd ..
xdev build


xchain-cli wasm deploy --account XC1234567890111111@xuper --cname buddha --fee 5000000 --runtime c ../buddhaContract/buddha/buddha.wasm

xchain-cli wasm upgrade --account XC1234567890111111@xuper --cname buddha --fee 5000000 ../buddhaContract/buddha/buddha.wasm


xchain-cli wasm invoke --fee 1000000 buddha --method find_kinddeed -a '{"id":"1"}' --account XC1234567890111111@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method add_kinddeed -a '{"id": "1", "name":"prodname","desc":"proddesc","price":"5", "count":"6","lasttime":"123456"}' --account XC1234567890111111@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method update_kinddeed -a '{"id": "1", "name":"prodname","desc":"proddesc","price":"5", "count":"6","lasttime":"123456"}' --account XC1234567890111111@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method del_kinddeed -a '{"id": "1"}'  --account XC1234567890111111@xuper

xchain-cli account balance XC1234567890111111@xuper
xchain-cli account balance XC1234567890222222@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method pray_kinddeed -a '{"id": "1","kinddeeds":"[{\"id\":\"1\",\"count\":\"1\"},{\"id\":\"1\",\"count\":\"2\"},{\"id\":\"1\",\"count\":\"3\"}]","amount":"30","timestamp":"11111"}' --account XC1234567890222222@xuper

xchain-cli wasm invoke --fee 1000000 buddha --method find_kinddeed -a '{"id":"1"}' --account XC1234567890222222@xuper

```
