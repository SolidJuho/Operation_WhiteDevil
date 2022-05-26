class CompleteObjective : ScriptedUserAction
{

	[Attribute("", UIWidgets.EditBox, "Interaction text", "")]
	protected string interactText;
	//------------------------------------------------------------------------------------------------
	override bool CanBeShownScript(IEntity user)
	{		
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity) 
	{	
		CollectItem ci = CollectItem.Cast(pOwnerEntity.FindComponent(CollectItem));
		ci.TryCollectItem();
	}
	

	//------------------------------------------------------------------------------------------------
	override bool GetActionNameScript(out string outName)
	{
		outName = interactText;
		return true;
	}


}