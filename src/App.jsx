import React, { PureComponent, Fragment } from 'react';
import { withRouter } from 'react-router-dom';
import { Route, Switch, Redirect } from 'react-router-dom';
import { connect } from 'react-redux';
import Welcome from './components/Welcome';
import Room from './components/Room';

import Footer from './components/Footer';

import './App.css';

class App extends PureComponent {
    render() {
        return (
            <div className="AppBox">
                <Switch>
                    {this.props.userState ? (
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
            userState: state.userState,
        }),
        {}
    )(App)
);
