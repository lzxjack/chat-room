import React, { PureComponent } from 'react';
import { withRouter } from 'react-router-dom';
import { connect } from 'react-redux';
import { login } from '../../redux/actions/userState';
import './index.css';

class Footer extends PureComponent {
    login = () => {
        this.props.login();
    };
    render() {
        return (
            <div className="footer">
                <span className="appName" onClick={this.login}>
                    简易聊天室
                </span>
            </div>
        );
    }
}

export default withRouter(connect(state => ({}), { login })(Footer));
