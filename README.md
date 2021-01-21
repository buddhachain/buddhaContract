# buddhaContract
buddhacontract


# 测试主键是否起作用

```bash
#创建合约账户
xchain-cli account new --account 1234567890111111 --fee 1000
xchain-cli transfer --to XC1234567890111111@xuper --amount 10000000000 --keys data/keys

xchain-cli account new --account 1234567890222222 --fee 1000
xchain-cli transfer --to XC1234567890222222@xuper --amount 10000000000 --keys data/keys

```


> protobuf 版本注意只能使用 3.7.1， fuck， 坑。

```bash
#生成协议源文件
cd src/
protoc --cpp_out=. exchange.proto

cd ..
xdev build


xchain-cli wasm deploy --account XC1234567890111111@xuper --cname exchange --fee 5000000 --runtime c ../buddhaContract/exchange/exchange.wasm

xchain-cli wasm invoke --fee 1000000 exchange --method find -a '{"id":"1"}'
xchain-cli wasm invoke --fee 1000000 exchange --method scan -a '{"id":"1"}'
xchain-cli wasm invoke --fee 1000000 exchange --method add -a '{"id": "1", "name":"prodname","desc":"proddesc","price":"5", "amount":"6","time":"7"}'
xchain-cli wasm invoke --fee 1000000 exchange --method del -a '{"id": "1"}'
xchain-cli wasm invoke --fee 1000000 exchange --method count


xchain-cli wasm upgrade --account XC1234567890111111@xuper --cname exchange --fee 5000000 ../buddhaContract/exchange/exchange.wasm
```
