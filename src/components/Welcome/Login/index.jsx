import React, { PureComponent, Fragment } from 'react';
import './index.css';

export default class Login extends PureComponent {
    render() {
        return (
            <Fragment>
                <input type="text" className="input" placeholder="输入用户名..." />
                <input type="password" className="input" placeholder="输入密码..." />
                <div class="enterBtn">登录</div>
            </Fragment>
        );
    }
}
