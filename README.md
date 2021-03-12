# buddhaContract






```



## 7. 善举上下架流程

### 7.1 添加删除修改善举类型

```bash
xchain-cli wasm invoke --fee 1000000 buddha --method add_kinddeedtype -a '{"id":"1", "desc":"事业顺心"}' --account XC1234567890222222@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method delete_kinddeedtype -a '{"id":"1"}' --account XC1234567890222222@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method update_kinddeedtype -a '{"id":"1", "desc":"事业顺心"}' --account XC1234567890222222@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method find_kinddeedtype -a '{"id":"1"}' --account XC1234567890555555@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method list_kinddeedtype --account XC1234567890222222@xuper

```


### 7.2 添加删除修改善举

```bash

#xchain-cli wasm invoke --fee 1000000 buddha --method add_kinddeeddetail -a '{"id":"1","sequence":"1","hash":"xxxxxx"}' --account XC1234567890444444@xuper
#xchain-cli wasm invoke --fee 1000000 buddha --method add_kinddeedspec -a '{"id":"1","sequence":"1","desc":"xxxxxx", "price":"10"}' --account XC1234567890444444@xuper


xchain-cli wasm invoke --fee 1000000 buddha --method add_kinddeed -a '{"id":"1", "name":"kd1", "type":"1", "lasttime":"xxxxxx", "detail":"[{\"sequence\":\"1\", \"hash\":\"xxxxxx\"},{\"sequence\":\"2\", \"hash\":\"yyyyyy\"}]", "spec":"[{\"sequence\":\"1\", \"desc\":\"aaaaaa\", \"price\":\"10\"},{\"sequence\":\"2\", \"desc\":\"bbbbbb\", \"price\":\"10\"}]" }' --account XC1234567890444444@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method delete_kinddeed -a '{"id":"1"}' --account XC1234567890444444@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method update_kinddeed -a '{"id":"1", "name":"kd1", "type":"1", "lasttime":"xxxxxx", "detail":[{"sequence":"1", "hash":"xxxxxx"},{"sequence":"2", "hash":"yyyyyy"}], "spec":[{"sequence":"1", "desc":"aaaaaa", "price":"10"},{"sequence":"2", "desc":"bbbbbb", "price":"10"}] }' --account XC1234567890444444@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method find_kinddeed -a '{"id":"1"}' --account XC1234567890222222@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method list_kinddeed --account XC1234567890222222@xuper

xchain-cli wasm invoke --fee 1000000 buddha --method list_kinddeeddetail -a '{"kdid":"1"}' --account XC1234567890222222@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method list_kinddeedspec -a '{"kdid":"1"}' --account XC1234567890222222@xuper

```

### 7.3 申请善举上架下架流程

```bash
xchain-cli wasm invoke --fee 1000000 buddha --method apply_online_kinddeed -a '{"id":"1"}' --account XC1234567890444444@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method approve_online_kinddeed -a '{"id":"1"}' --account XC1234567890222222@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method find_kinddeed -a '{"id":"1"}' --account XC1234567890222222@xuper

xchain-cli wasm invoke --fee 1000000 buddha --method apply_offline_kinddeed -a '{"id":"1"}' --account XC1234567890444444@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method approve_offline_kinddeed -a '{"id":"1"}' --account XC1234567890222222@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method find_kinddeed -a '{"id":"1"}' --account XC1234567890222222@xuper

```

## 8. 善举祈求及点评流程

### 8.1 添加删除修改点评标签

```bash
xchain-cli wasm invoke --fee 1000000 buddha --method add_commentlabel -a '{"id":"1", "desc":"处理及时"}' --account XC1234567890222222@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method delete_commentlabel -a '{"id":"1"}' --account XC1234567890222222@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method update_commentlabel -a '{"id":"1", "desc":"处理及时"}' --account XC1234567890222222@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method find_commentlabel -a '{"id":"1"}' --account XC1234567890555555@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method list_commentlabel --account XC1234567890222222@xuper

```

### 8.2 添加删除修改祈求善举前点评

```bash
xchain-cli wasm invoke --fee 1000000 buddha --method add_beforecomment -a '{"kdid":"1", "satisfaction":"0", "labels":"[\"1\"]","comment":"够前评论，不孬","timestamp":"xxxxxx"}' --account XC1234567890555555@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method delete_beforecomment -a '{"kdid":"1"}' --account XC1234567890555555@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method update_beforecomment -a '{"kdid":"1", "satisfaction":"0", "labels":"[\"1\"]","comment":"够前评论，不孬","timestamp":"xxxxxx"}' --account XC1234567890555555@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method find_beforecomment -a '{"kdid":"1","owner":"XC1234567890555555@xuper"}' --account XC1234567890222222@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method find_beforecomment -a '{"kdid":"1","owner":"XC1234567890555555@xuper"}' --account XC1234567890444444@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method find_beforecomment -a '{"kdid":"1"}' --account XC1234567890555555@xuper

xchain-cli wasm invoke --fee 1000000 buddha --method list_beforecomment -a '{"kdid":"1"}' --account XC1234567890222222@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method list_beforecomment -a '{"kdid":"1"}' --account XC1234567890444444@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method list_beforecomment -a '{"kdid":"1"}' --account XC1234567890555555@xuper

```

### 8.3 用户祈求善举

```bash
xchain-cli account balance XC1234567890555555@xuper

xchain-cli wasm invoke --fee 1000000 buddha --method pray_kinddeed -a '{"id": "1","kinddeed":"1","spec":"1","count":"2","timestamp":"11111"}' --account XC1234567890555555@xuper --amount 20
xchain-cli wasm invoke --fee 1000000 buddha --method delete_pray_kinddeed -a '{"id": "1"}' --account XC1234567890555555@xuper 
xchain-cli wasm invoke --fee 1000000 buddha --method find_pray_kinddeed -a '{"id": "1"}' --account XC1234567890555555@xuper 
xchain-cli wasm invoke --fee 1000000 buddha --method list_pray_kinddeed --account XC1234567890222222@xuper

```

### 8.4 基金会成员授权法师或寺院上传的善举凭证

```bash
xchain-cli account balance XC1234567890444444@xuper

xchain-cli wasm invoke --fee 1000000 buddha --method upload_kinddeedproof -a '{"orderid":"1", "proof":"xxxxx", "timestamp":"xxxxxx"}' --account XC1234567890444444@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method approve_kinddeedproof -a '{"orderid":"1"}' --account XC1234567890222222@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method refuse_kinddeedproof -a '{"orderid":"1"}' --account XC1234567890222222@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method find_kinddeedproof -a '{"orderid":"1"}' --account XC1234567890444444@xuper

xchain-cli wasm invoke --fee 1000000 buddha --method list_kinddeedproof --account XC1234567890222222@xuper

```


### 8.5 添加删除修改祈求善举后点评

```bash
xchain-cli wasm invoke --fee 1000000 buddha --method add_aftercomment -a '{"orderid":"1", "comment":"购前评价，不孬", "timestamp":"xxxxxx"}' --account XC1234567890555555@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method delete_aftercomment -a '{"orderid":"1"}' --account XC1234567890555555@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method update_aftercomment -a '{"orderid":"1", "comment":"购前评价，不孬", "timestamp":"xxxxxx"}' --account XC1234567890555555@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method find_aftercomment -a '{"orderid":"1"}' --account XC1234567890555555@xuper
xchain-cli wasm invoke --fee 1000000 buddha --method list_aftercomment --account XC1234567890222222@xuper

```