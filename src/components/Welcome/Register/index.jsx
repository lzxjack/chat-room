import React, { PureComponent, Fragment } from 'react';
import './index.css';

export default class Register extends PureComponent {
    render() {
        return (
            <Fragment>
                <input type="text" className="input inputReg" placeholder="输入用户名..." />
                <input type="password" className="input inputReg" placeholder="输入密码..." />
                <input type="password" className="input inputReg" placeholder="再次输入密码..." />
                <div class="enterBtn">注册</div>
            </Fragment>
        );
    }
}
