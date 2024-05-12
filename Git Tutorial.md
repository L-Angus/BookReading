## Git Tutorial

Git是分布式版本控制系统，SVN是集中式版本控制系统。

中心服务器可以交互用户的修改，Github就是中心服务器。

新建一个仓库之后，当前目录就成为了工作区，工作区下有一个隐藏目录 .git，它属于 Git 的版本库。

Git 的版本库有一个称为 Stage 的暂存区以及最后的 History 版本库，History 存储所有分支信息，使用一个 HEAD 指针指向当前分支。

![img](https://cs-notes-1256109796.cos.ap-guangzhou.myqcloud.com/image-20191208195941661.png)

工作区：本地目录，持有实际文件；

暂存区：修改区域，缓存开发者的修改；

HEAD: 指向最后一次提交的结果。

![1715514135191](C:\Users\lsd15\Documents\WeChat Files\wxid_kcrpyxkv7i7l22\FileStorage\Temp\1715514135191.png)



### 操作指令：

- 创建工作区

```shell
git init
```

- 克隆仓库

```shell
git clone <url: remoteurl>
```

- 把文件的修改添加的暂存区

```bash
git add <filename> : 添加某个文件的修改
git add . ：添加所有文件的修改
```

- 提交文件的修改到提交记录，HEAD指向它，提交之后stage的记录就清空了

```SHELL
git commit -m "提交信息"
git commit -F <filename>
```

- 推送提交到远程分支

```shell
git push origin master
```

如果你还没有克隆现有仓库，并欲将你的仓库连接到某个远程服务器，你可以使用如下命令添加：

```shell
git remote add origin <server>
```



### 分支指令：

- 创建分支并跳转到创建后的分支上

```shell
git checkout -b "branchname"
```

- 切换分支

```shell
git checkout <branchname>
```

- 删除分支

```shell
git branch -d <branchname>: 尝试删除
git branch -D <branchname>: 强制删除
```



### 更新、合并指令



