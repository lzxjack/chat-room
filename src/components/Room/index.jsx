import React, { PureComponent } from 'react';
import { ArrowRightOutlined } from '@ant-design/icons';
import './index.css';

export default class Room extends PureComponent {
    render() {
        return (
            <div className="RoomBox">
                <div className="centerBox">
                    <div className="messageBox"></div>
                    <div className="inputMsgBox">
                        <textarea className="inputMsg" />
                        <div className="sendBtn">
                            <ArrowRightOutlined />
                        </div>
                    </div>
                </div>
            </div>
        );
    }
}
