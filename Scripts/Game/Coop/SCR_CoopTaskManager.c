[EntityEditorProps(category: "GameScripted/Coop", description: "Allows task management.")]
class SCR_CoopTaskManagerClass : SCR_BaseTaskManagerClass
{
}

//------------------------------------------------------------------------------------------------
class SCR_CoopTaskManager : SCR_BaseTaskManager
{
	[Attribute("", UIWidgets.Auto, "Entity names of intial tasks - assigned to connecting players automatically.", category: "TaskManager: COOP")]
	protected ref array<string> m_aInitialTaskNames;

	[Attribute("US", UIWidgets.EditBox, "Faction key to assign to tasks.", category: "TaskManager: COOP")]
	protected FactionKey m_sAssignedFaction;

	//! Runtime instances for tasks created from initial task names
	protected ref array<SCR_BaseTask> m_aInitialTasks;

	protected RplComponent m_pRplComponent;
	
	
	//------------------------------------------------------------------------------------------------
	protected override void EOnInit(IEntity owner)
	{
		super.EOnInit(owner);
		
		// Do not initialize these tasks out of runtime
		if (!GetGame().InPlayMode())
			return;

		m_aInitialTasks = {};
		BaseWorld world = owner.GetWorld();
		foreach (string taskName : m_aInitialTaskNames)
		{
			IEntity entity = world.FindEntityByName(taskName);
			SCR_BaseTask task = SCR_BaseTask.Cast(entity);
			if (!task)
				continue;
			
			m_aInitialTasks.Insert(task);
		}

		m_pRplComponent = RplComponent.Cast(owner.FindComponent(RplComponent));
		if (!m_pRplComponent)
		{
			Print("SCR_CoopTaskManager is missing m_pRplComponent!", LogLevel.ERROR);
			return;
		}

		// Authority only
		if (!m_pRplComponent.IsMaster())
			return;

		Faction targetFaction = GetGame().GetFactionManager().GetFactionByKey(m_sAssignedFaction);
		if (!targetFaction)
		{
			Print("SCR_CoopTaskManager is missing Faction to assign tasks to!", LogLevel.ERROR);
			return;
		}

		foreach (SCR_BaseTask task : m_aInitialTasks)
		{
			if (!task)
				continue;

			task.SetTargetFaction(targetFaction);
		}
		
		
	}

	//------------------------------------------------------------------------------------------------
	protected override void OnPlayerRegistered(int registeredPlayerID)
	{
		super.OnPlayerRegistered(registeredPlayerID);

		SCR_BaseTaskExecutor taskExecutor = SCR_BaseTaskExecutor.GetTaskExecutorByID(registeredPlayerID);
		if (!taskExecutor)
		{
			Print("No execution can be executed because executing execution execute exec.");
			return;
		}
		
	}
}
