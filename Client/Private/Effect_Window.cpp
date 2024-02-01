#include "Effect_Window.h"
#include "../../Reference/Imgui/imgui.h"
#include "../../Reference/Imgui/imgui_impl_win32.h"
#include "../../Reference/Imgui/imgui_impl_dx11.h"

#include "GameInstance.h"
#include "Level_EffectTool.h"
#include "VIBuffer_Particle_Point.h"

IMPLEMENT_SINGLETON(CEffect_Window)

CEffect_Window::CEffect_Window()
{

}

HRESULT CEffect_Window::Initialize()
{
	m_pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(m_pGameInstance);

	return S_OK;
}

void CEffect_Window::Start()
{
}

void CEffect_Window::Tick(_float fTimeDelta)
{
}

HRESULT CEffect_Window::Render(ID3D11DeviceContext* pContext)
{
	//if (nullptr == this)
	//	return;

	ImGui::Begin(u8"ÀÌÆåÆ®Åø");
	if (ImGui::BeginTabBar("##EffectTabBar"))
	{



		//TODO ÀÌÆåÆ® ÅÇ ½ÃÀÛ
		//if (ImGui::BeginTabItem(u8"ÀÌÆåÆ®"))
		//{
		//	ImGui::Text(u8"ÀÌÆåÆ®");
		//	ImGui::EndTabItem();
		//}
		//TODO ÀÌÆåÆ® ÅÇ Á¾·á


		if (ImGui::BeginTabItem(u8"ÆÄÆ¼Å¬"))
		{
			ImGui::DragFloat("CamDistance", &m_fDistance, 0.1f, 0.f);
			//m_pEffectTool->Set_CamPos(m_fDistance);


			m_Desc = m_pEffectTool->Get_Desc();


			{
				float vCenter[3];
				vCenter[0] = m_Desc->ParticleDesc.vCenter.x;
				vCenter[1] = m_Desc->ParticleDesc.vCenter.y;
				vCenter[2] = m_Desc->ParticleDesc.vCenter.z;


				ImGui::DragFloat3("Center", vCenter, 0.1f, 0.f);

				m_Desc->ParticleDesc.vCenter.x = vCenter[0];
				m_Desc->ParticleDesc.vCenter.y = vCenter[1];
				m_Desc->ParticleDesc.vCenter.z = vCenter[2];

			}

			{
				float vCulling[3];
				vCulling[0] = m_Desc->ParticleDesc.vCulling.x;
				vCulling[1] = m_Desc->ParticleDesc.vCulling.y;
				vCulling[2] = m_Desc->ParticleDesc.vCulling.z;


				ImGui::DragFloat3("Culling", vCulling, 0.1f, 0.f);

				m_Desc->ParticleDesc.vCulling.x = vCulling[0];
				m_Desc->ParticleDesc.vCulling.y = vCulling[1];
				m_Desc->ParticleDesc.vCulling.z = vCulling[2];

			}

			{
				float vDestination[3];
				vDestination[0] = m_Desc->ParticleDesc.vDestination.x;
				vDestination[1] = m_Desc->ParticleDesc.vDestination.y;
				vDestination[2] = m_Desc->ParticleDesc.vDestination.z;


				ImGui::DragFloat3("Destination", vDestination, 0.1f, 0.f);

				m_Desc->ParticleDesc.vDestination.x = vDestination[0];
				m_Desc->ParticleDesc.vDestination.y = vDestination[1];
				m_Desc->ParticleDesc.vDestination.z = vDestination[2];

			}

			{
				float vRange[2];
				vRange[0] = m_Desc->ParticleDesc.vRange.x;
				vRange[1] = m_Desc->ParticleDesc.vRange.y;

				ImGui::DragFloat2("Range", vRange, 0.1f, 0.f);

				if (0 > vRange[0])
					vRange[0] = 0.f;

				if (vRange[0] > vRange[1])
					vRange[1] = vRange[0];

				m_Desc->ParticleDesc.vRange.x = vRange[0];
				m_Desc->ParticleDesc.vRange.y = vRange[1];
			}

			{
				float vScaleX[2];
				vScaleX[0] = m_Desc->ParticleDesc.vScaleX.x;
				vScaleX[1] = m_Desc->ParticleDesc.vScaleX.y;

				ImGui::DragFloat2("ScaleX", vScaleX, 0.1f, 0.f);

				if (0 > vScaleX[0])
					vScaleX[0] = 0.f;

				if (vScaleX[0] > vScaleX[1])
					vScaleX[1] = vScaleX[0];

				m_Desc->ParticleDesc.vScaleX.x = vScaleX[0];
				m_Desc->ParticleDesc.vScaleX.y = vScaleX[1];
			}

			{
				float vScaleY[2];
				vScaleY[0] = m_Desc->ParticleDesc.vScaleY.x;
				vScaleY[1] = m_Desc->ParticleDesc.vScaleY.y;

				ImGui::DragFloat2("ScaleY", vScaleY, 0.1f, 0.f);

				if (0 > vScaleY[0])
					vScaleY[0] = 0.f;

				if (vScaleY[0] > vScaleY[1])
					vScaleY[1] = vScaleY[0];

				m_Desc->ParticleDesc.vScaleY.x = vScaleY[0];
				m_Desc->ParticleDesc.vScaleY.y = vScaleY[1];
			}

			{
				float vSpeed[2];
				vSpeed[0] = m_Desc->ParticleDesc.vSpeed.x;
				vSpeed[1] = m_Desc->ParticleDesc.vSpeed.y;

				ImGui::DragFloat2("Speed", vSpeed, 0.1f, 0.f);

				if (0 > vSpeed[0])
					vSpeed[0] = 0.f;

				if (vSpeed[0] > vSpeed[1])
					vSpeed[1] = vSpeed[0];

				m_Desc->ParticleDesc.vSpeed.x = vSpeed[0];
				m_Desc->ParticleDesc.vSpeed.y = vSpeed[1];
			}

			{
				float fAcceleration;
				fAcceleration = m_Desc->ParticleDesc.fAcceleration;

				ImGui::DragFloat("Acceleration", &fAcceleration, 0.1f, 0.f);

				m_Desc->ParticleDesc.fAcceleration = fAcceleration;
			}

			{
				float vRotationX[2];
				vRotationX[0] = m_Desc->ParticleDesc.vRotationX.x;
				vRotationX[1] = m_Desc->ParticleDesc.vRotationX.y;

				ImGui::DragFloat2("RotationX", vRotationX, 1.f, 0.f);

				if (0 > vRotationX[0])
					vRotationX[0] = 0.f;

				if (vRotationX[0] > vRotationX[1])
					vRotationX[1] = vRotationX[0];

				m_Desc->ParticleDesc.vRotationX.x = vRotationX[0];
				m_Desc->ParticleDesc.vRotationX.y = vRotationX[1];
			}

			{
				float vRotationY[2];
				vRotationY[0] = m_Desc->ParticleDesc.vRotationY.x;
				vRotationY[1] = m_Desc->ParticleDesc.vRotationY.y;

				ImGui::DragFloat2("RotationY", vRotationY, 1.f, 0.f);

				if (0 > vRotationY[0])
					vRotationY[0] = 0.f;

				if (vRotationY[0] > vRotationY[1])
					vRotationY[1] = vRotationY[0];

				m_Desc->ParticleDesc.vRotationY.x = vRotationY[0];
				m_Desc->ParticleDesc.vRotationY.y = vRotationY[1];
			}

			{
				float vRotationZ[2];
				vRotationZ[0] = m_Desc->ParticleDesc.vRotationZ.x;
				vRotationZ[1] = m_Desc->ParticleDesc.vRotationZ.y;

				ImGui::DragFloat2("RotationZ", vRotationZ, 1.f, 0.f);

				if (0 > vRotationZ[0])
					vRotationZ[0] = 0.f;

				if (vRotationZ[0] > vRotationZ[1])
					vRotationZ[1] = vRotationZ[0];

				m_Desc->ParticleDesc.vRotationZ.x = vRotationZ[0];
				m_Desc->ParticleDesc.vRotationZ.y = vRotationZ[1];
			}

			{
				float vLifeTime[2];
				vLifeTime[0] = m_Desc->ParticleDesc.vLifeTime.x;
				vLifeTime[1] = m_Desc->ParticleDesc.vLifeTime.y;

				ImGui::DragFloat2("LifeTime", vLifeTime, 0.1f, 0.f);

				if (0 > vLifeTime[0])
					vLifeTime[0] = 0.f;

				if (vLifeTime[0] > vLifeTime[1])
					vLifeTime[1] = vLifeTime[0];

				m_Desc->ParticleDesc.vLifeTime.x = vLifeTime[0];
				m_Desc->ParticleDesc.vLifeTime.y = vLifeTime[1];

				m_pEffectTool->Set_MaxDelay(vLifeTime[1]);
			}



			ImGui::EndTabItem();
		}
		//! ÆÄÆ¼Å¬ ÅÇ Á¾·á
		ImGui::EndTabBar();
	}
	ImGui::End();

	return S_OK;
}

void CEffect_Window::Set_Level(CLevel_EffectTool* pLevel)
{
	m_pEffectTool = pLevel;
}

void CEffect_Window::Free()
{


	Safe_Release(m_pGameInstance);
	Safe_Release(m_pEffectTool);
}
