// Omid55
/*
 * create_network.cpp
 *
 *  Created on: Dec 26, 2013
 *      Author: oaskaris
 */

#include "stdafx.h"
#include "kronecker.h"
#include "eventinf.h"

int main(int argc, char* argv[])
{
  Env = TEnv(argc, argv, TNotify::StdNotify);
  Env.PrepArgs(TStr::Fmt("\nFlow network analytics. build: %s, %s. Time: %s", __TIME__, __DATE__, TExeTm::GetCurTm()));
  TExeTm ExeTm;
  Try

  const int TNetwork = Env.GetIfArgPrefixInt("-t:", -1, "Network to generate\n0:kronecker, 1:forest fire, 2:given structure in txt, generate flows & cascades, 3:given structure & flows, generate cascades (default:0)\n"); // network (kronecker, forest-fire, struct&rates given in txt)
  const TStr NetworkParams = Env.GetIfArgPrefixStr("-g:", TStr("0.9 0.5; 0.5 0.9"), "Parameters for the network (default:0.9 0.5; 0.5 0.9)\n"); // network params for kronecker/forest-fire
  const TStr GroundTruthFileName = Env.GetIfArgPrefixStr("-in:", TStr("input"), "Name of the input network if -t:2 (default:input)\n");  // input groundtruth, if any

  const TStr OutFNm  = Env.GetIfArgPrefixStr("-o:", "network", "Output file name(s) prefix");

  const int NNodes = Env.GetIfArgPrefixInt("-n:", 512, "Number of nodes (default:512)\n");
  const int NEdges = Env.GetIfArgPrefixInt("-e:", 1024, "Number of edges (default:1024)\n");

  bool verbose = true;

  TFNBs NBs;

  // set random seed
  TFlt::Rnd.Randomize();

  // generate network & flows
  if (TNetwork==0) {
	  PNGraph Graph;
	  TKronMtx SeedMtx;
	  TStr MtxNm;

	  printf("Kronecker graph for Ground Truth\n");
	  SeedMtx = TKronMtx::GetMtx(NetworkParams.CStr()); // 0.5,0.5,0.5,0.5

	  printf("\n*** Seed matrix:\n");
	  SeedMtx.Dump();

	  Graph = TKronMtx::GenFastKronecker(SeedMtx, (int)TMath::Log2(NNodes), NEdges, true, 0);

	  for (TNGraph::TNodeI NI = Graph->BegNI(); NI < Graph->EndNI(); NI++) { NBs.FlowNetwork.AddNode(NI.GetId()); }
	  for (TNGraph::TEdgeI EI = Graph->BegEI(); EI < Graph->EndEI(); EI++) { if (EI.GetSrcNId()==EI.GetDstNId()) { continue; } NBs.FlowNetwork.AddEdge(EI.GetSrcNId(),EI.GetDstNId()); }
  } else if (TNetwork==1) {
	  PNGraph Graph;
	  printf("Forest Fire graph for Ground Truth\n");
	  TStrV NetworkParamsV; NetworkParams.SplitOnAllCh(';', NetworkParamsV);

	  TFfGGen FF(false, // BurnExpFireP
			  NetworkParamsV[0].GetInt(), // StartNNodes (1)
			  NetworkParamsV[1].GetFlt(), // ForwBurnProb (0.2)
			  NetworkParamsV[2].GetFlt(), // BackBurnProb (0.17)
			  NetworkParamsV[3].GetInt(), // DecayProb (1)
			  NetworkParamsV[4].GetInt(), // Take2AmbasPrb (0)
			  NetworkParamsV[5].GetInt()); // OrphanPrb (0)

	  FF.GenGraph(NNodes, false);
	  Graph = FF.GetGraph();

	  for (TNGraph::TNodeI NI = Graph->BegNI(); NI < Graph->EndNI(); NI++) { NBs.FlowNetwork.AddNode(NI.GetId()); }
	  for (TNGraph::TEdgeI EI = Graph->BegEI(); EI < Graph->EndEI(); EI++) { if (EI.GetSrcNId()==EI.GetDstNId()) { continue; } NBs.FlowNetwork.AddEdge(EI.GetSrcNId(),EI.GetDstNId()); }
  }

  // save flow network
  NBs.SaveFlowNetworkTxt(TStr::Fmt("%s-network.txt", OutFNm.CStr()));


  Catch
  printf("\nrun time: %s (%s)\n", ExeTm.GetTmStr(), TSecTm::GetCurTm().GetTmStr().CStr());
  return 0;
}

