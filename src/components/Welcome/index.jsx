import React, { PureComponent } from 'react';
import MyNavLink from '../MyNavLink';
import { Route, Switch, Redirect } from 'react-router-dom';
import Login from './Login';
import Register from './Register';
import './index.css';

export default class Welcome extends PureComponent {
    render() {
        return (
            <div className="WelcomeBox">
                <div className="enter">
                    <div className="enterHeader">
                        <MyNavLink to="/welcome/login" className="welNav">
                            登录
                        </MyNavLink>
                        <MyNavLink to="/welcome/register" className="welNav">
                            注册
                        </MyNavLink>
                    </div>
                    <div className="enterBody">
                        <Switch>
                            <Route path="/welcome/login" component={Login} />
                            <Route path="/welcome/register" component={Register} />
                            <Redirect to="/welcome/login" />
                        </Switch>
                    </div>
                </div>
            </div>
        );
    }
}
