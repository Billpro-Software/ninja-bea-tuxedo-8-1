CREATE TABLE RM_DESTINATION_GROUP_INFO (
GROUP_ID varchar(150) PRIMARY KEY,
TIMESTAMP number ,
LAST_UPDATE number,
GROUP_EXPIRY_TIME number ,
REPLY_TO_URL varchar(150),
ENDPOINT_ADDRESS varchar(150),
LAST_MSG_NUM number);

CREATE TABLE RM_DESTINATION_MESSAGE_INFO (
GROUP_ID varchar(150) CONSTRAINT FK_DESTINATION_GROUP_ID REFERENCES RM_DESTINATION_GROUP_INFO ON DELETE CASCADE,
SEQUENCE_NUM number,
TIMESTAMP number,
LAST_UPDATE number,
ACK_STATUS varchar(50),
PROCESS_STATUS varchar(50),
REPLY_TO_URL varchar(150),
ENDPOINT_ADDRESS varchar(150),
FAULT_CODE varchar(50),
CONTENT_TYPE varchar(150),
SOAP_ACTION varchar(150),
MESSAGE BLOB,
PIPELINE_CONFIG BLOB,
CONSTRAINT RM_DESTINATION_MESSAGE_INFO_PK PRIMARY KEY (GROUP_ID, SEQUENCE_NUM));

CREATE TABLE RM_SOURCE_GROUP_INFO (
GROUP_ID varchar(150) PRIMARY KEY,
TIMESTAMP number ,
LAST_UPDATE number ,
GROUP_EXPIRY_TIME number ,
REPLY_TO_URL varchar(150),
ENDPOINT_ADDRESS varchar(150),
LAST_MSG_NUM number);

CREATE TABLE RM_SOURCE_MESSAGE_INFO (
GROUP_ID varchar(150) CONSTRAINT FK_SOURCE_GROUP_ID REFERENCES RM_SOURCE_GROUP_INFO ON DELETE CASCADE,
SEQUENCE_NUM number,
TIMESTAMP number,
LAST_UPDATE number,
RETRY_COUNT number,
ACK_STATUS varchar(50),
PROCESS_STATUS varchar(50),
REPLY_TO_URL varchar(150),
ENDPOINT_ADDRESS varchar(150),
FAULT_CODE varchar(50),
CONTENT_TYPE varchar(150),
SOAP_ACTION varchar(150),
MESSAGE BLOB,
PIPELINE_CONFIG BLOB,
CONSTRAINT RM_SOURCE_MESSAGE_INFO_PK PRIMARY KEY (GROUP_ID, SEQUENCE_NUM));

COMMIT;
