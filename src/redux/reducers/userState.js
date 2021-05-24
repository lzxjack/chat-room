import { LOGIN, LOGOUT } from '../constant';

// 设定初始状态
const initState = false;

export default function addReducer(preState = initState, action) {
    const { type } = action;
    switch (type) {
        case LOGIN:
            return true;
        case LOGOUT:
            return false;
        default:
            return preState;
    }
}
