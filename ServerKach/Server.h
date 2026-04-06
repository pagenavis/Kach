#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QMap>
#include <QTimer>
#include <QDateTime>
#include "UserManager.h"

struct SocketInfo {
    QTcpSocket* socket;
    bool authenticated;
    int userId = -1;
    QByteArray buffer;
    quint32 expectedSize;
    QString clientIp;
    QDateTime connectionTime;
    QDateTime lastActivityTime;
    qint64 bytesReceived = 0;
    int packetCount = 0;
    SocketInfo() : socket(nullptr), authenticated(false), userId(-1), expectedSize(0), bytesReceived(0), packetCount(0) {}
};

class Server : public QTcpServer
{
    Q_OBJECT

public:
    explicit Server(QObject *parent = nullptr);
    ~Server();

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private slots:
    void slotReadyRead();
    void removeSocket();
    void checkInactiveConnections();  // ✅ Новый слот

private:
    // === DDoS Protection ===
    static constexpr int MAX_TOTAL_CONNECTIONS = 200;
    static constexpr int MAX_CONNECTIONS_PER_IP = 20;
    static constexpr int CONNECTION_TIMEOUT_MS = 300000;      // 5 мин на аутентификацию
    static constexpr int INACTIVITY_TIMEOUT_MS = 600000;      // 10 мин неактивности
    static constexpr qint64 MAX_BYTES_PER_SECOND = 10485760;  // 10 MB/s
    static constexpr int MAX_PACKETS_PER_SECOND = 1000;

    bool isRateLimited(const QString& clientIp);
    void cleanupOldTimestamps();

    QMap<QString, int> ipConnectionCount;
    QMap<QString, QVector<qint64>> ipPacketTimestamps;
    QTimer* inactivityCheckTimer;
    // === End DDoS Protection ===

    void SendToClient(QTcpSocket* clientSocket, const QString& str);
    void SendImageToClient(QTcpSocket* clientSocket, int user_id, const QByteArray& imageData);
    void SendImageToClient(QTcpSocket* clientSocket, int measurement_id, const QByteArray& imageData, const QString& photoType);
    void processCommand(QTcpSocket* currentSocket, const QString& command);
    void handleGetWorkoutProgress(QTcpSocket* currentSocket, const QString& command);
    void handleMarkWorkoutDone(QTcpSocket* currentSocket, const QString& command);
    int findSocketIndex(QTcpSocket* sock);
    QTcpSocket* findSocketByUserId(int userId);
    bool checkCredentials(const QString& login, const QString& password);

    QList<SocketInfo> Sockets;
    UserManager UserManagers;

    QByteArray imageBuffer;
    quint64 expectedImageSize;
    bool isReceivingImage;
    int currentImageUserId;
    QString currentPhotoType;
    int currentMeasurementId;

    quint32 requireSize;
    bool comlexData;
};

#endif // SERVER_H
