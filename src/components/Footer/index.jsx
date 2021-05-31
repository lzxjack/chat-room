import React, { PureComponent } from 'react';
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
                    干饭聊天室
                </span>
            </div>
        );
    }
}

export default connect(state => ({}), { login })(Footer);
