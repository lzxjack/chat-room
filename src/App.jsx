import React, { PureComponent, Fragment } from 'react';
import { withRouter } from 'react-router-dom';
import { Route, Switch, Redirect } from 'react-router-dom';
import { connect } from 'react-redux';
import Welcome from './components/Welcome';
import Room from './components/Room';
import { login, logout } from './redux/actions/userState';

import Footer from './components/Footer';

import './App.css';

class App extends PureComponent {
    // 启动应用时，判断是否已经登录
    // componentDidMount() {
    //     if (!localStorage.getItem('token')) {
    //         this.props.logout();
    //     } else {
    //         this.props.login(localStorage.getItem('name'));
    //     }
    // }
    render() {
        return (
            <div className="AppBox">
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
                <Footer />
            </div>
        );
    }
}

export default withRouter(
    connect(
        state => ({
            loginState: state.userState.loginState,
        }),
        { login, logout }
    )(App)
);
