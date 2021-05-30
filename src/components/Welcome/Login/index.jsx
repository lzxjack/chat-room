import React, { PureComponent, Fragment } from 'react';
// import { withRouter } from 'react-router-dom';
import { connect } from 'react-redux';
import axios from '../../../utils/axios/config';
import { login } from '../../../redux/actions/userState';
import './index.css';

class Login extends PureComponent {
    login = async () => {
        // const url = `http://47.110.144.145:4567/login?name=${this.inputUname.value}&pwd=${this.inputPwd.value}`;
        const url = 'http://47.110.144.145:4567/login';
        // axios.get(url).then(
        //     response => {
        //         const res = response.data;
        //         console.log(res);
        //         if (res.login === 0) {
        //             // window.localStorage.setItem(token, res.token);
        //             this.props.login();
        //         }
        //     },
        //     error => {
        //         console.log(error);
        //     }
        // );
        axios({
            method: 'get',
            url,
            params: {
                name: this.inputUname.value,
                pwd: this.inputPwd.value,
            },
        })
            .then(res => {
                console.log(res.data);
                if (res.data.login === 0) {
                    localStorage.setItem('token', res.data.token);
                    this.props.login();
                } else {
                    console.log('登陆失败！');
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

export default connect(state => ({}), { login })(Login);
