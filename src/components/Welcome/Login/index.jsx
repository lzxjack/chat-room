import React, { PureComponent, Fragment } from 'react';
import axios from 'axios';
import './index.css';

export default class Login extends PureComponent {
    login = () => {
        const url = `http://47.110.144.145:4567?name=${this.inputUname.value}&pwd=${this.inputPwd.value}`;
        axios.get(url).then(
            response => {
                console.log(response);
            },
            error => {
                console.log(error);
            }
        );
    };
    render() {
        return (
            <Fragment>
                <input
                    ref={c => (this.inputUname = c)}
                    type="text"
                    className="input"
                    placeholder="输入用户名..."
                />
                <input
                    ref={c => (this.inputPwd = c)}
                    type="password"
                    className="input"
                    placeholder="输入密码..."
                />
                <div className="enterBtn" onClick={this.login}>
                    登录
                </div>
            </Fragment>
        );
    }
}
