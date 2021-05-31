import React, { PureComponent } from 'react';
import { ArrowRightOutlined } from '@ant-design/icons';
import { connect } from 'react-redux';
import { message } from 'antd';
import moment from 'moment';
import { nanoid } from 'nanoid';
import axios from '../../utils/axios/config';
import './index.css';

class Room extends PureComponent {
    state = {
        msg: [],
    };

    componentDidMount() {
        this.getMsg();
        this.msgUpdate = setInterval(() => {
            this.getMsg();
        }, 1000);
    }
    componentWillUnmount() {
        // 清除定时器
        clearInterval(this.msgUpdate);
    }

    // 获取所需消息
    getMsg = () => {
        const url = 'http://47.110.144.145:4567/information';
        const name = this.props.name;
        axios({
            method: 'get',
            url,
            params: { name },
            // responseType: 'blob',
        })
            .then(res => {
                // console.log(res);
                // 获取新数据
                const newMsg = res.data.msg;
                // 获取原数据
                const oldMsg = this.state.msg;
                if (res.data.information === 0) {
                    this.setState({ msg: [...oldMsg, ...newMsg] }, () => {
                        // 滚动条自动到底部
                        this.messageBox.scrollTop = this.messageBox.scrollHeight;
                    });
                }
            })
            .catch(err => console.error(err));
    };

    // 发送消息
    sendMsg = () => {
        const msg = this.editMsg.value;
        const name = this.props.name;
        if (msg === '') {
            message.warning('请输入消息！');
            return;
        }
        const url = 'http://47.110.144.145:4567/information';
        axios({
            method: 'post',
            url,
            params: {
                msg,
                name,
                time: new Date().getTime(),
                id: nanoid(),
            },
            // responseType: 'blob',
        })
            .then(res => {
                // console.log(res);
                if (res.data.msg === 0) {
                    this.editMsg.value = '';
                    message.success('发送成功！');
                    // 调用获取所有消息函数
                    this.getMsg();
                }
            })
            .catch(err => console.error(err));
    };
    onEnter = e => {
        // const msg = this.editMsg.value;
        // if (msg === '') {
        //     message.warning('请输入消息！');
        //     return;
        // }
        // e.preventDefault();
        if (e.keyCode === 13) {
            this.sendMsg();
        }
    };
    render() {
        return (
            <div className="RoomBox">
                {/* 中间居中盒子 */}
                <div className="centerBox">
                    {/* 聊天记录 */}
                    <ul className="messageBox" ref={c => (this.messageBox = c)}>
                        {this.state.msg.map(msgObj => {
                            return (
                                <li
                                    className={
                                        msgObj.name === this.props.name ? 'msgLi myself' : 'msgLi'
                                    }
                                    key={msgObj.id}
                                >
                                    <div className="msgName">
                                        <span>{msgObj.name}</span>&nbsp;&nbsp;&nbsp;
                                        <span className="msgTime">
                                            {moment(msgObj.time).format('YYYY-MM-DD HH:mm:ss')}
                                        </span>
                                    </div>
                                    {/* URI解码 */}
                                    <div className="msgContent">{decodeURI(msgObj.msg)}</div>
                                </li>
                            );
                        })}
                    </ul>
                    {/* 输入区域 */}
                    <div className="inputMsgBox">
                        <textarea
                            ref={c => (this.editMsg = c)}
                            className="inputMsg"
                            onKeyUp={this.onEnter}
                            onKeyDown={event => {
                                // 阻止默认换行行为
                                if (event.keyCode === 13) event.preventDefault();
                            }}
                        />
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
