import { LOGIN, LOGOUT } from '../constant';

// 设定初始状态
const initState = {
    loginState: false,
    name: '',
};

export default function addReducer(preState = initState, action) {
    const { type, data } = action;
    switch (type) {
        case LOGIN:
            return {
                loginState: true,
                name: data,
            };
        case LOGOUT:
            return {
                loginState: false,
                name: '',
            };
        default:
            return preState;
    }
}
