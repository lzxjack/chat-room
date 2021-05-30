import React, { PureComponent } from 'react';
import { ArrowRightOutlined } from '@ant-design/icons';
import { connect } from 'react-redux';
import { message } from 'antd';
import axios from '../../utils/axios/config';
import './index.css';

class Room extends PureComponent {
    componentDidMount() {}

    sendMsg = () => {
        const msg = this.editMsg.value;
        const name = this.props.name;
        if (msg === '') {
            msg.warning('请输入消息！');
            return;
        }
        const url = 'http://47.110.144.145:4567/information';
        axios({
            method: 'post',
            url,
            params: {
                msg,
                name,
            },
        })
            .then(res => {
                if (res.data.information === 0) {
                    message.success('发送成功！');
                    // 调用获取所有消息函数
                }
            })
            .catch(err => console.error(err));
    };
    render() {
        return (
            <div className="RoomBox">
                {/* 中间居中盒子 */}
                <div className="centerBox">
                    {/* 聊天记录 */}
                    <ul className="messageBox">
                        <li className="msgLi">
                            <div className="msgName">jack</div>
                            <div className="msgContent">hello</div>
                        </li>
                    </ul>
                    {/* 输入区域 */}
                    <div className="inputMsgBox">
                        <textarea ref={c => (this.editMsg = c)} className="inputMsg" />
                        <div className="sendBtn" onClick={this.sendMsg}>
                            <ArrowRightOutlined />
                        </div>
                    </div>
                </div>
            </div>
        );
    }
}

export default connect(
    state => ({
        name: state.userState.name,
    }),
    {}
)(Room);
