# task

2021-02-05
工时：2h
1. 测试添加及判断当前用户角色，is_deployer, is_founder, is_master, is_user, 测试通过。
2. 测试申请成为基金会成员 apply_founder, 批准资格 approve_founder, 取消资格 recusel_fonder, 抵押金退还等，测试通过。
3. 测试申请成为法师或寺院 apply_master, 批准资格 approve_master, 取消资格 recusel_master, 测试通过。
4. 测试申请添加善举add_kinddeed, 删除善举delete_kinddeed, 修改善举update_kinddeed，测试通过。
5. 测试申请善举上架 apply_online_kinddeed, 批准上架 approve_online_kinddeed，测试通过。
6. 测试申请善举下架 apply_offline_kinddeed, 批准下架 approve_offline_kinddeed，测试通过。
7. 测试祈求善举 pray_kinddeed，测试通过。
8. 测试上传善举凭证 upload_kinddeed_proof, 批准善举凭证 approve_kinddeed_proof, 取消善举凭证 recusel_kinddeed_proof, 测试通过。


代码已经上传

提示：
- 精度不在合约内体现。所有的精度问题由外部决定。外部可以任意更换精度。
- 目前正常流程，基本测试通过。非正常流程尚未测试，预估存在诸多bug。不排除依旧存在重构的可能性。

问题：
1. 拒绝成为基金会成员时，直接删除表项，表中无法记录拒绝的原因。
2. 拒绝成为法师时，直接删除表项，表中无法记录拒绝的原因。
 