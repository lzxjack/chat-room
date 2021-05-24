import { LOGIN, LOGOUT } from '../constant';

export const login = data => ({
    type: LOGIN,
    data,
});

export const login = data => ({
    type: LOGOUT,
    data,
});
