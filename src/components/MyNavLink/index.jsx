import React, { PureComponent } from 'react';
import { NavLink } from 'react-router-dom';

export default class MyNavLink extends PureComponent {
    render() {
        return <NavLink activeClassName="active" {...this.props} />;
    }
}
