> 😃 本人能力有限，欢迎大佬指正改进~ 现在聊天室后台经常挂掉，就没再打开过了😅😅 今后会加以改进，重新上线！🤠
>
> 🖥️应用预览地址：<a href="https://chat-room-1gn38h2w40ab28f3-1304393382.ap-shanghai.app.tcloudbase.com" target="_blank">[点击这里]</a>

# 1. 应用简介

## 主要功能

1. 用户注册
2. 用户登录
3. 发送、接收消息
4. 退出功能

## 主要用到的技术

**前端：**

1. React 脚手架`Create-React-App`
2. 状态管理`redux` + `react-redux`等
3. 前端路由 `React-Router`、路由鉴权
4. 少量使用 `AntD` 组件库 （`Icon` 图标、`Notification` 通知提醒框、`Message` 全局提示）

这里仅记录了前端的相关技术，后端基于`TCP`/`HTTP`协议，采用 C/C++实现，详情请查看<a href="https://github.com/dwnb/chat_web" target="_blank">[GitHub]</a>。

# 2. 主要功能实现

## 1. 路由鉴权

将用户的登录状态放入`redux`，默认为`false`未登录。

当`App`组件挂载时，判断用户登录状态，若已经登录，则直接跳转到`聊天室页面`；若未登录，则跳转到`注册/登录页面`，让用户登录。

```javascript
<Switch>
    {this.props.loginState ? (
        <Fragment>
            <Route path="/room" component={Room} />
            <Redirect to="/room" />
        </Fragment>
    ) : (
        <Fragment>
            <Route path="/welcome" component={Welcome} />
            <Redirect to="/welcome" />
        </Fragment>
    )}
</Switch>
```

## 2. 用户注册

需要验证用户填写的用户名、密码是否符合规范，若不符合规范给出提示并直接`return`，若符合规范才发送注册请求给服务器。

```javascript
// 点击按钮，登录
register = () => {
    // 数字字母组合，字母开头
    const unameReg = /^[a-zA-Z][a-zA-Z0-9]{2,9}$/;
    const uname = this.uname.value;
    const pwd = this.pwd.value;
    const pwdAgian = this.pwdAgian.value;
    // 判断用户名是否符合规则
    if (!unameReg.test(uname)) {
        this.openUnameError();
        return;
    }
    // 判断密码长度
    if (!(pwd.length >= 6 && pwd.length <= 16)) {
        this.openPwdError();
        return;
    }
    // 判断两次输入的密码是否一致
    if (pwd !== pwdAgian) {
        this.openPwdUnEqual();
        return;
    }
    // 调用接口，发送注册请求
    const url = `${constUrl}/register`;
    axios({
        method: 'get',
        url,
        params: {
            name: uname,
            pwd,
        },
    })
        .then(res => {
            // 注册成功
            if (res.data.register === 0) {
                this.openRegisterSuccess();
                this.uname.value = '';
                this.pwd.value = '';
                this.pwdAgian.value = '';
                // 跳转到登录页
                this.props.history.replace(`/welcome/login`);
            } else {
                // 注册失败，打开相应的提示框
                switch (res.data.error) {
                    case 0: {
                        this.openUnameReuse();
                        return;
                    }
                    default: {
                        this.openOtherError();
                        return;
                    }
                }
            }
        })
        .catch(err => console.error(err));
};
```

## 3. 用户登录

登录功能没什么好说的，收集参数并发送请求就可以了，若登录成功，则给出提示，并更改`redux`中的登录状态为`true`，页面自动会跳转到聊天室页面。若登陆失败，则根据服务器返回的数据，给出相应提示。

```javascript
login = async () => {
    const url = `${constUrl}/login`;
    const name = this.inputUname.value;
    const pwd = this.inputPwd.value;
    axios({
        method: 'get',
        url,
        params: {
            name,
            pwd,
        },
    })
        .then(res => {
            if (res.data.login === 0) {
                this.props.login(name);
                this.openLoginSuccess();
                return;
            }
            switch (res.data.error) {
                case 0: {
                    this.openUnameNotFound();
                    this.props.logout();
                    return;
                }
                case 1: {
                    this.openPwdError();
                    this.props.logout();
                    return;
                }
                case 2: {
                    this.openOtherError();
                    this.props.logout();
                    return;
                }
                default:
                    return;
            }
        })
        .catch(err => console.error(err));
```

## 4. 接收消息

接受消息功能，同样也是向服务器发送请求，获得所需消息，并展示在页面上。

这里需要将展示聊天记录容器的滚动条自动调整到底部，详情见<a href="https://blog.csdn.net/Jack_lzx/article/details/117444212" target="_blank">JavaScript 实现容器滚动条默认出现在底部位置</a>。

由于发送一次接收消息的请求，只能得到一次消息，所以我在`componentDidMount()`生命周期函数中，开启了一个定时器，每隔 1 秒就发送一次请求，获得所有消息，展示到页面上。由于 React 的`diff`算法，即使没有新的消息，频繁地发送请求，也不会有浪费太多性能。记得在`componentWillUnmount()`中，清除定时器。

```javascript
componentDidMount() {
    this.getMsg();
    this.msgUpdate = setInterval(() => {
        this.getMsg();
    }, 1000);
}
componentWillUnmount() {
    // 清除定时器
    clearInterval(this.msgUpdate);
}
```

```javascript
// 获取所需消息
getMsg = () => {
    const url = `${constUrl}/information`;
    const name = this.props.name;
    axios({
        method: 'get',
        url,
        params: { name },
        // responseType: 'blob',
    })
        .then(res => {
            console.log(res);
            // 获取人数
            const userCount = res.data.userCount;
            this.setState({ userCount });
            // 获取新数据
            const newMsg = res.data.msg;
            // 获取原数据
            const oldMsg = this.state.msg;
            if (res.data.information === 0) {
                this.setState({ msg: [...oldMsg, ...newMsg] }, () => {
                    // 滚动条自动到底部
                    this.messageBox.scrollTop = this.messageBox.scrollHeight;
                });
            }
        })
        .catch(err => console.error(err));
};
```

## 5. 发送消息

发送请求之前，先判断输入框是否为空。不为空，再进行下一步，发送请求。

成功发送消息后，调用一次`接收消息`函数，获得所有消息，即可将刚刚发送的消息立即展示到页面。

```javascript
   // 发送消息
   sendMsg = () => {
    const msg = this.editMsg.value;
    const name = this.props.name;
    if (msg === '') {
        message.warning('请输入消息！');
        return;
    }
    const url = `${constUrl}/information`;
    axios({
        method: 'post',
        url,
        params: {
            msg,
            name,
            time: new Date().getTime(),
            id: nanoid(),
        },
    })
        .then(res => {
            // console.log(res);
            if (res.data.msg === 0) {
                this.editMsg.value = '';
                message.success('发送成功！');
                // 调用获取所有消息函数
                this.getMsg();
            }
        })
        .catch(err => console.error(err));
```

## 6. 退出功能

退出时，发送请求给服务器，告诉服务器有用户退出了、哪个用户退出了，主要用于展示当前在线人数。

将`redux`中的登录状态改为`false`，页面自动跳转到`注册/登录`页面。

```javascript
logout = () => {
    const url = `${constUrl}/logout`;
    const name = this.props.name;
    axios({
        method: 'get',
        url,
        params: {
            name,
        },
    });
    this.openLogout();
    this.props.logout();
};
```

# 3. Todo

由于本人能力有限，本 Demo 还有一些`BUG`没有解决：

1. 当前在数人数显示模块没有正常工作，若用户不点击`退出`按钮，直接关闭浏览器页面，没有监听到用户的退出动作。
2. 接收到的消息中，`空格`、`?`、`=`、`#`等字符会显示其编码，无法正常显示。

**将来可能添加的功能：**

1. 采用`token`验证用户身份

2. 自定义背景图片切换

3. 支持黑暗模式

4. 适配移动端

5. 支持上传头像

6. 支持发送图片

    ...
