[ComponentEditorProps(category: "GameScripted/CollectItem", description: "")]
class CollectItemClass: ScriptComponentClass
{
};

class CollectItem : ScriptComponent
{
	[Attribute("", UIWidgets.EditBox, "Objective name.", category: "Objective Data")]
	string objName;
	[Attribute("", UIWidgets.EditBox, "Objective title.", category: "Objective Data")]
	string objTitle;
	[Attribute("", UIWidgets.EditBox, "Objective description.", category: "Objective Data")]
	string objDesc;
	[Attribute("", UIWidgets.EditBox, "Objective unlock.", category: "Objective Data")]
	string unlockObj;
	
	void TryCollectItem()
	{
		Rpc(RpcAsk_CompleteObj, GetOwner().GetName());
	}
	
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_CompleteObj(string entityName)
	{
		//Send hint to all.
		SCR_BaseTask task = SCR_BaseTask.Cast(GetGame().GetWorld().FindEntityByName(objName));
		task.Finish();
		GetTaskManager().FinishTask(task);
		
		Rpc(RpcDo_CompleteObj);
		SCR_EntityHelper.DeleteEntityAndChildren(GetGame().GetWorld().FindEntityByName(entityName));
		if(unlockObj != "")
		{
			SCR_CoopTaskManager coopTM = SCR_CoopTaskManager.Cast(GetTaskManager());
			coopTM.UnlockObjective(unlockObj);
		}
	}	
	
	[RplRpc(RplChannel.Reliable, RplRcver.Broadcast)]
	protected void RpcDo_CompleteObj()
	{
		SCR_HintManagerComponent hintComponent = SCR_HintManagerComponent.GetInstance();
		hintComponent.ShowCustomHint(objDesc, objTitle, 10);
		
	}
}