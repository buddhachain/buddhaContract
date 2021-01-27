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
protoc --cpp_out=. exchange.proto

cd ..
xdev build


xchain-cli wasm deploy --account XC1234567890111111@xuper --cname exchange --fee 5000000 --runtime c ../buddhaContract/exchange/exchange.wasm

xchain-cli wasm upgrade --account XC1234567890111111@xuper --cname exchange --fee 5000000 ../buddhaContract/exchange/exchange.wasm


xchain-cli wasm invoke --fee 1000000 exchange --method product_find -a '{"id":"1"}' --account XC1234567890111111@xuper
xchain-cli wasm invoke --fee 1000000 exchange --method product_scan -a '{"id":"1"}' --account XC1234567890111111@xuper
xchain-cli wasm invoke --fee 1000000 exchange --method product_add -a '{"id": "1", "name":"prodname","desc":"proddesc","price":"5", "count":"6","lasttime":"123456"}' --account XC1234567890111111@xuper
xchain-cli wasm invoke --fee 1000000 exchange --method product_update -a '{"id": "1", "name":"prodname","desc":"proddesc","price":"5", "count":"6","lasttime":"123456"}' --account XC1234567890111111@xuper
xchain-cli wasm invoke --fee 1000000 exchange --method product_del -a '{"id": "1"}'  --account XC1234567890111111@xuper

xchain-cli account balance XC1234567890111111@xuper
xchain-cli account balance XC1234567890222222@xuper
xchain-cli wasm invoke --fee 1000000 exchange --method buy -a '{"id": "1","products":"[{\"id\":\"1\",\"count\":\"1\"},{\"id\":\"1\",\"count\":\"2\"},{\"id\":\"1\",\"count\":\"3\"}]","amount":"30","timestamp":"11111"}' --account XC1234567890222222@xuper

xchain-cli wasm invoke --fee 1000000 exchange --method product_find -a '{"id":"1"}' --account XC1234567890222222@xuper

```
