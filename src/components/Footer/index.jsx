import React, { PureComponent } from 'react';
import { connect } from 'react-redux';
import { login } from '../../redux/actions/userState';
import './index.css';

class Footer extends PureComponent {
    render() {
        return (
            <div className="footer">
                <span className="appName">干饭聊天室</span>
            </div>
        );
    }
}

export default connect(state => ({}), { login })(Footer);
