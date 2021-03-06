-- SQL Script for OAAM
-- &&1 - Audit Admin Role
-- &&2 - Audit Append Role
-- &&3 - Audit Viewer Role

CREATE TABLE OAAM (
	IAU_ID NUMBER , 
	IAU_TstzOriginating TIMESTAMP , 
	IAU_EventType VARCHAR(255) , 
	IAU_EventCategory VARCHAR(255) , 
	IAU_ActionNotes VARCHAR(4000) , 
	IAU_CaseActionEnum VARCHAR(4000) , 
	IAU_CaseActionResult NUMBER , 
	IAU_CaseChallengeQuestion VARCHAR(4000) , 
	IAU_CaseChallengeResult NUMBER , 
	IAU_CaseDisposition VARCHAR(4000) , 
	IAU_CaseExprDurationInHrs INTEGER , 
	IAU_CaseId NUMBER , 
	IAU_CaseIds VARCHAR(4000) , 
	IAU_CaseSeverity VARCHAR(4000) , 
	IAU_CaseStatus VARCHAR(4000) , 
	IAU_CaseSubActionEnum INTEGER , 
	IAU_Description VARCHAR(4000) , 
	IAU_GroupId NUMBER , 
	IAU_GroupIds VARCHAR(4000) , 
	IAU_GroupName VARCHAR(4000) , 
	IAU_GroupDetails VARCHAR(4000) , 
	IAU_GroupElementId NUMBER , 
	IAU_GroupElementIds VARCHAR(4000) , 
	IAU_GroupElementValue VARCHAR(4000) , 
	IAU_GroupElementsDetails VARCHAR(4000) , 
	IAU_KBACategoryId NUMBER , 
	IAU_KBACategoryIds VARCHAR(4000) , 
	IAU_KBACategoryName VARCHAR(4000) , 
	IAU_KBACategoryDetails VARCHAR(4000) , 
	IAU_KBAQuestionId NUMBER , 
	IAU_KBAQuestionIds VARCHAR(4000) , 
	IAU_KBAQuestion VARCHAR(4000) , 
	IAU_KBAQuestionType INTEGER , 
	IAU_KBAQuestionDetails VARCHAR(4000) , 
	IAU_KBAValidationId NUMBER , 
	IAU_KBAValidationIds VARCHAR(4000) , 
	IAU_KBAValidationName VARCHAR(4000) , 
	IAU_KBAValidationDetails VARCHAR(4000) , 
	IAU_KBARegLogicDetails VARCHAR(4000) , 
	IAU_KBAAnswerLogicDetails VARCHAR(4000) , 
	IAU_LoginId VARCHAR(255) , 
	IAU_PolicyDetails VARCHAR(4000) , 
	IAU_PolicyId NUMBER , 
	IAU_PolicyIds VARCHAR(4000) , 
	IAU_PolicyName NUMBER , 
	IAU_PolicyOverrideDetails VARCHAR(4000) , 
	IAU_PolicyOverrideId NUMBER , 
	IAU_PolicyOverrideIds VARCHAR(4000) , 
	IAU_PolicyOverrideRowId NUMBER , 
	IAU_PolicyRuleMapId NUMBER , 
	IAU_PolicyRuleMapIds VARCHAR(4000) , 
	IAU_PolicyRuleMapDetails VARCHAR(4000) , 
	IAU_RuleId NUMBER , 
	IAU_RuleConditionId NUMBER , 
	IAU_RuleConditionIds VARCHAR(4000) , 
	IAU_RuleName VARCHAR(4000) , 
	IAU_RuleDetails VARCHAR(4000) , 
	IAU_RuleConditionMapId NUMBER , 
	IAU_RuleConditionMapIds VARCHAR(4000) , 
	IAU_RuleParamValueDetails VARCHAR(4000) , 
	IAU_SourcePolicyId NUMBER , 
	IAU_UserGroupName VARCHAR(255) , 
	IAU_UserId NUMBER , 
	IAU_UserIds VARCHAR(4000) 
);

-- INDEX 
CREATE INDEX OAAM_Index
ON OAAM(IAU_TSTZORIGINATING);

-- PERMISSIONS 
GRANT ALL on OAAM to &&1;
GRANT INSERT on OAAM to &&2;
GRANT SELECT on OAAM to &&3;

-- SYNONYMS 
CREATE OR REPLACE SYNONYM &&3..OAAM FOR &&1..OAAM;
CREATE OR REPLACE SYNONYM &&2..OAAM FOR &&1..OAAM;
