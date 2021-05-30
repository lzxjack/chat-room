import React, { PureComponent, Fragment } from 'react';
import { connect } from 'react-redux';
import { notification } from 'antd';
import { CloseOutlined, CheckOutlined } from '@ant-design/icons';
import axios from '../../../utils/axios/config';
import { login, logout } from '../../../redux/actions/userState';
import './index.css';

class Login extends PureComponent {
    openLoginSuccess = () => {
        notification.open({
            message: '登录成功！',
            description: '欢迎使用聊天室！',
            icon: <CheckOutlined />,
            placement: 'bottomLeft',
            duration: 1.5,
        });
    };
    openUnameNotFound = () => {
        notification.open({
            message: '登录失败！',
            description: '用户名不存在，请检查用户名。',
            icon: <CloseOutlined />,
        });
    };
    openPwdError = () => {
        notification.open({
            message: '登录失败！',
            description: '用户名和密码不匹配。',
            icon: <CloseOutlined />,
        });
    };
    openOtherError = () => {
        notification.open({
            message: '登录失败！',
            description: '网络故障，请重试。',
            icon: <CloseOutlined />,
        });
    };
    login = async () => {
        const url = 'http://47.110.144.145:4567/login';
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
                    localStorage.setItem('token', res.data.token);
                    localStorage.setItem('name', name);
                    this.props.login(name);
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

export default connect(state => ({}), { login, logout })(Login);
