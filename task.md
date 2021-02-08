# task

2021-02-07
工时：4h
1. 测试普通用户是否可以调用合约，结论，可以

xchain-cli transfer --to gbRjavZajSVuv6oKRbBqH9RaNCsjhetbr --amount 1000000 --keys data/keys
xchain-cli wasm invoke --fee 1000 buddha --method find_pray_kinddeed -a '{"id": "1"}' --keys data/testuser

2. 合约合约健壮性优化。
3. 性能测试。


代码已经上传

明日计划:
1. 为各个表提供可能的索引接口


提示：
- 精度不在合约内体现。所有的精度问题由外部决定。外部可以任意更换精度。
- 目前正常流程，基本测试通过。非正常流程尚未测试，预估存在诸多bug。不排除依旧存在重构的可能性。

问题：
1. 拒绝成为基金会成员时，直接删除表项，表中无法记录拒绝的原因。
2. 拒绝成为法师时，直接删除表项，表中无法记录拒绝的原因。

后续任务：
1. 正常流程联调
2. 调研平行链
3. 修改合约bug
4. 主链合约性能测试