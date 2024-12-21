#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib") // Winsock library
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cooperation.h"
#include "definition.h"
#include <thread>
#include <stdexcept>  // 包含标准异常类
#include <cstring>    // 包含 memset

USING_NS_CC;

// 监听线程函数
void listenThread() {
    char buffer[1024];
    int bytesRead;

    while (true) {
        std::memset(buffer, 0, sizeof(buffer));  // 清空缓冲区
        // 接收服务器发送的消息
        bytesRead = recv(global_socket, buffer, sizeof(buffer), 0);
        if (bytesRead > 0)
        {
            // 检查消息是否为文本
            bool isTextMessage = true;
            for (int i = 0; i < bytesRead; ++i) {
                if (buffer[i] < 32 || buffer[i] > 126) {  // 检查是否为可打印字符
                    isTextMessage = false;
                    CCLOG("wtf");
                    break;
                }
            }
            // 将接收到的消息转换为字符串
            std::string receivedMessage(buffer, bytesRead);
            CCLOG("Received from server: %s", receivedMessage.c_str());
            try {
                // 根据消息内容执行不同的操作
                if (receivedMessage.find("MATCHED") != std::string::npos) {
                    handleMatchedMessage(receivedMessage);
                }
                else if (receivedMessage.find("TREE") != std::string::npos) {
                    //handleTreeActionMessage(receivedMessage);
                }
                else if (receivedMessage.find("MOVE") != std::string::npos) {
                    //handlePlayerMoveMessage(receivedMessage);
                }
                else if (receivedMessage.find("PLOUGH") != std::string::npos) {
                    //handlePloughActionMessage(receivedMessage);
                }
                else if (receivedMessage.find("MINNER") != std::string::npos) {
                    //handleMineActionMessage(receivedMessage);
                }
                else if (receivedMessage.find("HARVEST") != std::string::npos) {
                    //handleHarvestActionMessage(receivedMessage);
                }
                else {
                    // 未知消息，抛出异常
                    throw std::runtime_error("Unknown message: " + receivedMessage);
                }
            }
            catch (const std::exception& e) {
                // 捕获并处理异常
                std::cerr << "Error: " << e.what() << std::endl;
                CCLOG("Original message: %s", receivedMessage.c_str());
            }
        }
        else if (bytesRead == 0) {
            // 服务器关闭连接
            std::cout << "Server closed the connection." << std::endl;
            break;
        }
        else {
            // 接收失败
            std::cerr << "Error receiving data from server: " << WSAGetLastError() << std::endl;
            break;
        }
    }

    // 关闭套接字
    closesocket(global_socket);
    global_socket = INVALID_SOCKET;
}

// 启动监听线程
void startListeningThread() {
    // 创建新线程来监听服务器消息
    std::thread listener(listenThread);
    listener.detach(); // 分离线程，使其独立运行
}

// 发送消息到服务器
void sendMessageToServer(const std::string& message) {
    if (global_socket == INVALID_SOCKET) {
        std::cerr << "Socket is not connected." << std::endl;
        return;
    }

    // 发送消息
    int bytesSent = send(global_socket, message.c_str(), message.size(), 0);
    if (bytesSent == SOCKET_ERROR) {
        std::cerr << "Error sending message to server: " << WSAGetLastError() << std::endl;
    }
    else {
        std::cout << "Sent to server: " << message << std::endl;
    }
}

// 连接到服务器
bool connectToServer() {
    // 初始化 Winsock
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        return false;
    }

    // 创建套接字
    global_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (global_socket == INVALID_SOCKET) {
        std::cerr << "Error creating socket: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return false;
    }

    // 设置服务器地址
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr);

    // 连接到服务器
    if (connect(global_socket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Error connecting to server: " << WSAGetLastError() << std::endl;
        closesocket(global_socket);
        WSACleanup();
        return false;
    }

    std::cout << "Connected to server: " << SERVER_IP << ":" << PORT << std::endl;
    return true;
}

// 清理 Winsock
void cleanupWinsock() {
    if (global_socket != INVALID_SOCKET) {
        closesocket(global_socket);
    }
    WSACleanup();
}

// 监听服务器信号的线程函数
void listen_server_signal(SOCKET sock) {
    char buffer[1024] = { 0 };
    fd_set read_fds; // 用于 select 的文件描述符集合
    struct timeval timeout;
    timeout.tv_sec = 10; // 设置超时时间为 10 秒
    timeout.tv_usec = 0;

    while (true) {
        FD_ZERO(&read_fds);
        FD_SET(sock, &read_fds);

        // 使用 select 等待数据
        int activity = select(0, &read_fds, nullptr, nullptr, &timeout);
        if (activity == 0) {
            // 超时，关闭线程
            CCLOG("Timeout: No message received from server in 10 seconds.");
            break;
        }
        else if (activity < 0) {
            // 错误，关闭线程
            CCLOG("Error: Failed to listen for server signal.");
            break;
        }

        // 检查是否有数据可读
        if (FD_ISSET(sock, &read_fds)) {
            int valread = recv(sock, buffer, 1024, 0);
            if (valread > 0) {
                // 接收到消息，输出到日志
                CCLOG("Received message from server: %s", buffer);
                break; // 关闭线程
            }
            else {
                // 服务器断开连接
                CCLOG("Server disconnected.");
                break;
            }
        }
    }
}

// 初始化合作界面
bool scene_coop::init() {
    if (!Scene::init()) {
        return false;
    }

    // 获取屏幕大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建背景图片层
    auto backgroundSprite = Sprite::create("menu/background.png");
    if (backgroundSprite) {
        // 设置背景图片的大小以适应屏幕
        backgroundSprite->setScaleX(visibleSize.width / backgroundSprite->getContentSize().width);
        backgroundSprite->setScaleY(visibleSize.height / backgroundSprite->getContentSize().height);

        // 设置背景图片的位置（居中）
        backgroundSprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

        // 将背景图片添加到场景中
        this->addChild(backgroundSprite, 0); // 层级为 0（最底层）
    }
    else {
        CCLOG("Failed to load background image!");
    }

    // 创建标题
    auto titleLabel = Label::createWithTTF("Choose Cooperation Mode", "fonts/Marker Felt.ttf", 48);
    titleLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 100));
    this->addChild(titleLabel);

    // 创建“创建”按钮
    auto createButton = ui::Button::create("menu/button_normal.png", "menu/button_pressed.png"); // 替换为你的按钮图片
    createButton->setTitleText("Create");
    createButton->setTitleFontName("fonts/Marker Felt.ttf"); // 设置字体文件
    createButton->setTitleFontSize(70);
    createButton->setTitleColor(Color3B(205, 133, 63)); // 设置文字颜色为棕黄色
    createButton->setPosition(Vec2(origin.x + visibleSize.width / 2 - 400, origin.y + visibleSize.height / 2));
    createButton->addClickEventListener(CC_CALLBACK_1(scene_coop::onCreate, this));
    this->addChild(createButton);

    // 创建“加入”按钮
    auto joinButton = ui::Button::create("menu/button_normal.png", "menu/button_pressed.png");
    joinButton->setTitleText("Join");
    joinButton->setTitleFontName("fonts/Marker Felt.ttf"); // 设置字体文件
    joinButton->setTitleFontSize(70);
    joinButton->setTitleColor(Color3B(205, 133, 63)); // 设置文字颜色为棕黄色
    joinButton->setPosition(Vec2(origin.x + visibleSize.width / 2 + 400, origin.y + visibleSize.height / 2));
    joinButton->addClickEventListener(CC_CALLBACK_1(scene_coop::onJoin, this));
    this->addChild(joinButton);

    return true;
}

// 创建按钮回调
void scene_coop::onCreate(Ref* sender) {
    // 切换到创建界面
    auto createScene = scene_create::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, createScene));
}

// 加入按钮回调
void scene_coop::onJoin(Ref* sender) {
    // 切换到加入界面
    auto joinScene = scene_join::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, joinScene));
}

/* 初始化创建界面 */
bool scene_create::init() {
    if (!Scene::init()) {
        return false;
    }

    // 获取屏幕大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建背景图片层
    auto backgroundSprite = Sprite::create("menu/background.png");
    if (backgroundSprite) {
        // 设置背景图片的大小以适应屏幕
        backgroundSprite->setScaleX(visibleSize.width / backgroundSprite->getContentSize().width);
        backgroundSprite->setScaleY(visibleSize.height / backgroundSprite->getContentSize().height);

        // 设置背景图片的位置（居中）
        backgroundSprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

        // 将背景图片添加到场景中
        this->addChild(backgroundSprite, 0); // 层级为 0（最底层）
    }
    else {
        CCLOG("Failed to load background image!");
    }

    // 创建标题
    auto titleLabel = Label::createWithTTF("Create a Room", "fonts/Marker Felt.ttf", 48);
    titleLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 100));
    this->addChild(titleLabel);

    // 创建邀请码文本框
    auto inviteCodeLabel = Label::createWithTTF("Please Create an Invitation Code", "fonts/Marker Felt.ttf", 32);
    inviteCodeLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 50));
    this->addChild(inviteCodeLabel);

    // 创建文本框背景图
    auto textBoxSprite = Sprite::create("menu/textBox.png"); // 替换为你的背景图片路径
    textBoxSprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 50));
    textBoxSprite->setContentSize(Size(300, 50)); // 设置背景图的大小与 EditBox 一致
    this->addChild(textBoxSprite, 1); // 添加到场景中，层级为 0（最底层）

    // 创建待输入文本框
    auto inputBox = ui::TextField::create("Enter something...", "fonts/Marker Felt.ttf", 32);
    inputBox->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 50));
    inputBox->setMaxLength(20); // 设置最大输入长度
    inputBox->setPlaceHolderColor(Color4B(128, 128, 128, 255)); // 设置占位符颜色
    inputBox->setCursorEnabled(true); // 启用光标
    inputBox->setCursorChar('|'); // 设置光标字符
    inputBox->setCursorPosition(0); // 设置光标位置
    inputBox->setTouchEnabled(true); // 启用触摸事件
    inputBox->addClickEventListener([](Ref* sender) {
        // 处理点击事件
        });
    this->addChild(inputBox, 2);

    // 创建“确定”按钮
    auto confirmButton = ui::Button::create("menu/button_normal.png", "menu/button_pressed.png"); // 替换为你的按钮图片
    confirmButton->setTitleText("OK"); // 设置按钮文字为 "OK"
    confirmButton->setTitleFontName("fonts/Marker Felt.ttf"); // 设置字体文件
    confirmButton->setTitleFontSize(80);
    confirmButton->setTitleColor(Color3B(205, 133, 63)); // 设置文字颜色为棕黄色
    confirmButton->setPosition(Vec2(origin.x + visibleSize.width / 2 + 220, origin.y + visibleSize.height / 2 - 50));
    confirmButton->setScale(0.3f); // 将背景图片缩小到原始大小的一半
    confirmButton->addClickEventListener([inputBox](Ref* sender) {
        // 获取用户输入
        std::string userInput = inputBox->getString();
        CCLOG("User input: %s", userInput.c_str());
        // 处理用户输入的逻辑
        // 初始化客户端
        WSADATA wsaData;
        struct sockaddr_in server_addr;

        // 初始化 Winsock
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            CCLOG("Winsock initialization failed.");
            return -1;
        }

        // 创建 socket
        if ((global_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
            CCLOG("Socket creation failed: ");
            WSACleanup();
            return -1;
        }

        // 设置服务器地址
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(PORT);

        // 将 IP 地址转换为网络字节序
        if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
            CCLOG("Invalid address/ Address not supported.");
            closesocket(global_socket);
            WSACleanup();
            return -1;
        }

        // 连接到服务器
        if (connect(global_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
            CCLOG("Connection failed: ");
            closesocket(global_socket);
            WSACleanup();
            return -1;
        }
        CCLOG("Connected to server.");
        sendMessageToServer("CREATE_COOP " + userInput);

        // 切换到 ConnectingScene
        CCLOG("Switching to ConnectingScene...");
        auto connecting_Scene = ConnectingScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, connecting_Scene));
        CCLOG("Scene switched to ConnectingScene.");
        });
    this->addChild(confirmButton, 3);

    return true;
}

/* 初始化加入界面 */
bool scene_join::init() {
    if (!Scene::init()) {
        return false;
    }

    // 获取屏幕大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建背景图片层
    auto backgroundSprite = Sprite::create("menu/background.png");
    if (backgroundSprite) {
        // 设置背景图片的大小以适应屏幕
        backgroundSprite->setScaleX(visibleSize.width / backgroundSprite->getContentSize().width);
        backgroundSprite->setScaleY(visibleSize.height / backgroundSprite->getContentSize().height);

        // 设置背景图片的位置（居中）
        backgroundSprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

        // 将背景图片添加到场景中
        this->addChild(backgroundSprite, 0); // 层级为 0（最底层）
    }
    else {
        CCLOG("Failed to load background image!");
    }

    // 创建标题
    auto titleLabel = Label::createWithTTF("Join a Room", "fonts/Marker Felt.ttf", 48);
    titleLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 100));
    this->addChild(titleLabel);

    // 创建邀请码文本框
    auto inviteCodeLabel = Label::createWithTTF("Please Enter the Invitation Code", "fonts/Marker Felt.ttf", 32);
    inviteCodeLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 50));
    this->addChild(inviteCodeLabel);

    // 创建文本框背景图
    auto textBoxSprite = Sprite::create("menu/textBox.png");
    textBoxSprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 50));
    textBoxSprite->setContentSize(Size(300, 50)); // 设置背景图的大小与 EditBox 一致
    this->addChild(textBoxSprite, 1); // 添加到场景中，层级为 0（最底层）

    // 创建待输入文本框
    auto inputBox = ui::TextField::create("Enter something...", "fonts/Marker Felt.ttf", 32);
    inputBox->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 50));
    inputBox->setMaxLength(20); // 设置最大输入长度
    inputBox->setPlaceHolderColor(Color4B(128, 128, 128, 255)); // 设置占位符颜色
    inputBox->setCursorEnabled(true); // 启用光标
    inputBox->setCursorChar('|'); // 设置光标字符
    inputBox->setCursorPosition(0); // 设置光标位置
    inputBox->setTouchEnabled(true); // 启用触摸事件
    inputBox->addClickEventListener([](Ref* sender) {
        // 处理点击事件
        });
    this->addChild(inputBox, 2);

    // 创建“确定”按钮
    auto confirmButton = ui::Button::create("menu/button_normal.png", "menu/button_pressed.png"); // 替换为你的按钮图片
    confirmButton->setTitleText("OK"); // 设置按钮文字为 "OK"
    confirmButton->setTitleFontName("fonts/Marker Felt.ttf"); // 设置字体文件
    confirmButton->setTitleFontSize(80);
    confirmButton->setTitleColor(Color3B(205, 133, 63)); // 设置文字颜色为棕黄色
    confirmButton->setPosition(Vec2(origin.x + visibleSize.width / 2 + 220, origin.y + visibleSize.height / 2 - 50));
    confirmButton->setScale(0.3f); // 将背景图片缩小到原始大小的一半
    confirmButton->addClickEventListener([inputBox](Ref* sender) {
        // 获取用户输入
        std::string userInput = inputBox->getString();
        CCLOG("User input: %s", userInput.c_str());
        // 处理用户输入的逻辑
        // 初始化客户端
        WSADATA wsaData;
        struct sockaddr_in server_addr;

        // 初始化 Winsock
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            CCLOG("Winsock initialization failed.");
            return -1;
        }

        // 创建 socket
        if ((global_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
            CCLOG("Socket creation failed: ");
            WSACleanup();
            return -1;
        }

        // 设置服务器地址
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(PORT);

        // 将 IP 地址转换为网络字节序
        if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
            CCLOG("Invalid address/ Address not supported.");
            closesocket(global_socket);
            WSACleanup();
            return -1;
        }

        // 连接到服务器
        if (connect(global_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
            CCLOG("Connection failed: ");
            closesocket(global_socket);
            WSACleanup();
            return -1;
        }
        CCLOG("Connected to server.");
        sendMessageToServer("CONNECT_COOP " + userInput);

        // 切换到 ConnectingScene
        CCLOG("Switching to ConnectingScene...");
        auto connecting_Scene = ConnectingScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, connecting_Scene));
        CCLOG("Scene switched to ConnectingScene.");
        });
    this->addChild(confirmButton, 3);

    return true;
}

/* 初始化 ConnectingScene */
bool ConnectingScene::init() {
    if (!Scene::init()) {
        return false;
    }

    // 获取屏幕大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建背景图片层
    auto backgroundSprite = Sprite::create("menu/background.png");
    if (backgroundSprite) {
        // 设置背景图片的大小以适应屏幕
        backgroundSprite->setScaleX(visibleSize.width / backgroundSprite->getContentSize().width);
        backgroundSprite->setScaleY(visibleSize.height / backgroundSprite->getContentSize().height);

        // 设置背景图片的位置（居中）
        backgroundSprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

        // 将背景图片添加到场景中
        this->addChild(backgroundSprite, 0); // 层级为 0（最底层）
    }
    else {
        CCLOG("Failed to load background image!");
    }

    // 创建 "connecting..." 文本框
    auto connectingLabel = Label::createWithTTF("Connecting...", "fonts/Marker Felt.ttf", 48);
    connectingLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(connectingLabel);

    // 启动监听线程
    startListeningThread();

    return true;
}

void handleMatchedMessage(std::string receivedMessage) {
    
    CCLOG("connected!!!");
}