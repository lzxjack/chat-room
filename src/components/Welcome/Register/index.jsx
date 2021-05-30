import React, { PureComponent, Fragment } from 'react';
import { notification, Button } from 'antd';
import { CloseOutlined, CheckOutlined } from '@ant-design/icons';
import axios from '../../../utils/axios/config';
import './index.css';

export default class Register extends PureComponent {
    openRegisterSuccess = () => {
        const key = `open${Date.now()}`;
        const btn = (
            <Button type="primary" size="small" onClick={() => notification.close(key)}>
                好的
            </Button>
        );
        notification.open({
            message: '注册成功！',
            description: '使用用户名密码登录吧！',
            btn,
            key,
            icon: <CheckOutlined />,
            duration: 0,
        });
    };
    openUnameReuse = () => {
        notification.open({
            message: '注册失败！',
            description: '用户名已被注册，请更换迎户名。',
            icon: <CloseOutlined />,
        });
    };
    openUnameError = () => {
        notification.open({
            message: '注册失败！',
            description: '用户名长度在3~10之间，数字字母组合，英文字母开头。',
            icon: <CloseOutlined />,
        });
    };
    openPwdError = () => {
        notification.open({
            message: '注册失败！',
            description: '密码长度在6~16之间。',
            icon: <CloseOutlined />,
        });
    };
    openPwdUnEqual = () => {
        notification.open({
            message: '注册失败！',
            description: '两次密码不一致，请确认密码。',
            icon: <CloseOutlined />,
        });
    };
    openOtherError = () => {
        notification.open({
            message: '注册失败！',
            description: '网络故障，请重试。',
            icon: <CloseOutlined />,
        });
    };
    // 点击按钮，登录
    register = () => {
        // 数字字母组合，字母开头，3~10位
        const unameReg = /^[a-zA-Z][a-zA-Z0-9]{2,9}$/;
        const uname = this.uname.value;
        const pwd = this.pwd.value;
        const pwdAgian = this.pwdAgian.value;
        if (!unameReg.test(uname)) {
            this.openUnameError();
            return;
        }
        if (!(pwd.length >= 6 && pwd.length <= 16)) {
            this.openPwdError();
            return;
        }
        if (pwd !== pwdAgian) {
            this.openPwdUnEqual();
            return;
        }
        const url = 'http://47.110.144.145:4567/login';
        axios({
            method: 'get',
            url,
            params: {
                name: uname,
                pwd,
            },
        })
            .then(res => {
                // 登录成功
                if (res.data.register === 0) {
                    this.openRegisterSuccess();
                    this.uname.value = '';
                    this.pwd.value = '';
                    this.pwdAgian.value = '';
                    // 跳转到登录页
                    this.props.history.replace(`/welcome/login`);
                } else {
                    // 登陆失败
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
    render() {
        return (
            <Fragment>
                <input
                    ref={c => (this.uname = c)}
                    type="text"
                    className="input inputReg"
                    placeholder="输入用户名..."
                />
                <input
                    ref={c => (this.pwd = c)}
                    type="password"
                    className="input inputReg"
                    placeholder="输入密码..."
                />
                <input
                    ref={c => (this.pwdAgian = c)}
                    type="password"
                    className="input inputReg"
                    placeholder="再次输入密码..."
                />
                <div class="enterBtn" onClick={this.register}>
                    注册
                </div>
            </Fragment>
        );
    }
}
