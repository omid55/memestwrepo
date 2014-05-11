#ifndef snap_eventinf_h
#define snap_eventinf_h

#include "snap/Snap.h"

typedef TNodeEDatNet<TFltV, TFltV> TFltVFltVNet;
typedef TPt<TFltVFltVNet> PFltFltVNet;

typedef TNodeEDatNet<TFltIntPrV, TFltIntPrV> TFltIntPrVFltIntPrVNet;
typedef TPt<TFltIntPrVFltIntPrVNet> PFltIntPrVFltIntPrVNet;

typedef TNodeEDatNet<TFlt, TFlt> TFltFltNet;
typedef TPt<TFltFltNet> PFltFltNet;

typedef TNodeNet<TFltIntPrV> TFltIntPrVNet;
typedef TPt<TFltIntPrVNet> PFltIntPrVNet;

// Hit info (node id, timestamp, sentiment) about a node in a cascade
class THitInfo {
public:
  TInt NId;
  TFlt Tm;
public:
  THitInfo(const int& NodeId=-1, const double& HitTime=0) : NId(NodeId), Tm(HitTime) { }
  THitInfo(TSIn& SIn) : NId(SIn), Tm(SIn) { }
  void Save(TSOut& SOut) const { NId.Save(SOut); Tm.Save(SOut); }
  bool operator < (const THitInfo& Hit) const {
    return Tm < Hit.Tm; }
};

// Cascade
class TCascade {
public:
  TInt CId; // cascade id
  THash<TInt, THitInfo> NIdHitH; // infected nodes
public:
  TCascade() : CId(0), NIdHitH() { }
  TCascade(const int &cid) : CId(cid), NIdHitH() { }
  TCascade(TSIn& SIn) : CId(SIn), NIdHitH(SIn) { }
  TCascade(const TCascade& Cascade) : CId(Cascade.CId), NIdHitH(Cascade.NIdHitH) { }

  void Save(TSOut& SOut) const  { CId.Save(SOut); NIdHitH.Save(SOut); }
  void Clr() { NIdHitH.Clr(); }

  int GetId() { return CId; }
  int Len() const { return NIdHitH.Len(); }
  int LenBeforeT(const double& T) { int len = 0; while (len < NIdHitH.Len() && NIdHitH[len].Tm <= T) { len++; } return len; }
  int LenAfterT(const double& T) { int len = 0; while (len < NIdHitH.Len() && NIdHitH[NIdHitH.Len()-1-len].Tm >= T) { len++; } return len; }
  int GetNode(const int& i) const { return NIdHitH.GetKey(i); }
  void GetNodesBeforeT(const double& T, TIntV& NIdV) { int len = 0; while (len < NIdHitH.Len() && NIdHitH[len].Tm <= T) { NIdV.Add(NIdHitH[len].NId); len++; } return; }
  void GetNodesAfterT(const double& T, TIntV& NIdV) { int len = 0; while (len < NIdHitH.Len() && NIdHitH[NIdHitH.Len()-1-len].Tm >= T) { NIdV.Add(NIdHitH[NIdHitH.Len()-1-len].NId); len++; } return; }
  THash<TInt, THitInfo>::TIter BegI() const { return NIdHitH.BegI(); }
  THash<TInt, THitInfo>::TIter EndI() const { return NIdHitH.EndI(); }
  double GetTm(const int& NId) const { return NIdHitH.GetDat(NId).Tm; }
  double GetMaxTm() const { return NIdHitH[NIdHitH.Len()-1].Tm; } // we assume the cascade is sorted
  double GetMinTm() const { return NIdHitH[0].Tm; } // we assume the cascade is sorted
  double GetMedianTm() const { return (Len()%2==0? NIdHitH[Len()/2].Tm.Val : (NIdHitH[Len()/2].Tm.Val+NIdHitH[Len()/2+1].Tm.Val)/2.0); }
  void Add(const int& NId, const double& HitTm) { NIdHitH.AddDat(NId, THitInfo(NId, HitTm)); }
  void Del(const int& NId) { NIdHitH.DelKey(NId); }
  bool IsNode(const int& NId) const { return NIdHitH.IsKey(NId); }
  void Sort() { NIdHitH.SortByDat(true); }
  bool operator < (const TCascade& Cascade) const {
      return Len() < Cascade.Len(); }
};

// Stochastic gradient network inference class
class TFNBs {
public:
  // events, hashtags, flow and bursts network
  TFltVFltVNet EventsNetwork;
  TFltIntPrVFltIntPrVNet EventsUrlNetwork;
  TFltIntPrVNet HashtagsNetwork;
  TFltIntPrVNet UrlRedirectionNetwork;
  TFltIntPrVNet RetweetConventionNetwork;
  TFltFltNet FlowNetwork;
  TFltIntPrVFltIntPrVNet BurstLevelsEventsNetwork;

  // Omid55
  TFltV Casc_times;
  // Omid55

  // in-flow burstiness
  THash<TInt, TFltIntPrV> BurstLevelsInFlows;

  // followers network
  TNGraph FollowersNetwork;

  // username, user id
  TStrIntH NodeNmH;

  // Hashtags, hashtag id
  TStrIntH HashtagNmH;

  // url redirection name
  TStrIntH UrlRedirectionNmH;

  // retweet convention name
  TStrIntH RetweetConventionNmH;

  // url address (url diffusion)
  TStrIntH UrlAddressNmH;

  TIntFltH InFlowPerNode;

  // in-flow retweet delay likelihood
  THash<TInt, TFltPrV> RetweetDelayCdfInflow;

  THash<TInt, TCascade> CascH;

public:
  TFNBs( ) { }
  TFNBs(TSIn& SIn) : EventsNetwork(SIn), HashtagsNetwork(SIn), FlowNetwork(SIn), FollowersNetwork(SIn), NodeNmH(SIn) { }
  void Save(TSOut& SOut) const
  {
	  // Omid55
	  Casc_times.Save(SOut);
	  // Omid55

	  EventsNetwork.Save(SOut); HashtagsNetwork.Save(SOut); FlowNetwork.Save(SOut); FollowersNetwork.Save(SOut); NodeNmH.Save(SOut);
  }

  // functions to load/save flow network files
  void LoadFlowNetworkTxt(TSIn& SIn);
  void SaveFlowNetworkTxt(const TStr& OutFNm);

  // function to load node names / node id's
  void LoadNodeNamesFromLiteSQL(const int &NumUsers=-1);
  void LoadFollowersNetworkFromTxt(const int &NumUsers=-1);
  void LoadFollowersNetworkFromPostgreSQL(const int& NumUsers);

  // function to load events network from postgresql
  // Omid55
  void LoadCascadeOfQuoteFromPostgreSQL(TStr& DesiredQuote);
  //void LoadCascadeOfQuoteFromPostgreSQL(THash<TUInt,TSecTmV>& result, const THash<TStr,TUInt>& quotesContent, const int &NumUsers=-1, const TStr& StartDate=TStr("2008-10-01 00:00:00"), const TStr& EndDate=TStr("2009-10-01 00:00:00"));
  // Omid55

  void LoadEventsNetworkFromPostgreSQL(const int &NumUsers=-1, const TStr& StartDate=TStr("2008-10-01 00:00:00"), const TStr& EndDate=TStr("2009-10-01 00:00:00"));
  void LoadUrlEventsNetworkFromPostgreSQL(const int &NumUsers=-1, const TStr& StartDate=TStr("2008-10-01 00:00:00"), const TStr& EndDate=TStr("2009-10-01 00:00:00"));
  void LoadRetweetConventionNetworkFromPostgreSQL(const int& NumUsers, const TStr& StartDate=TStr("2008-10-01 00:00:00"), const TStr& EndDate=TStr("2009-10-01 00:00:00"));
  void LoadHashtagNetworkFromPostgreSQL(const int& NumUsers=-1, const TStr& StartDate=TStr("2008-10-01 00:00:00"), const TStr& EndDate=TStr("2009-10-01 00:00:00"));
  void LoadUrlRedirectionNetworkFromPostgreSQL(const int& NumUsers=-1, const TStr& StartDate=TStr("2008-10-01 00:00:00"), const TStr& EndDate=TStr("2009-10-01 00:00:00"));

  // node info
  int GetNodes() { return EventsNetwork.GetNodes(); }

  // compute flow networks
  void ComputeStationaryFlow(const TStr& StartDate, const TStr& EndDate);
  void ComputeBurstLevelEvents(const int& k, const double& s, const double& gamma);

  // functions to compute burstiness (Kleinberg, KDD'02)
  void find_C(TFltV &x, TFltVV &C, const int& k, const double& s, const double& gamma, const double& T);
  void find_min_state(TFltVV &C, TIntV &states, const int& k, const double& s, const double& gamma, const double& T);
  void LabelBurstAutomaton(TFltV& EventTimes, TIntV &state_labels, const int& k = 5, const double& s = 2.0, const double& gamma = 1.0);

  void GenCascade(TCascade& C, const double& beta, const double& thr, const int& no_time);
  int GetCascs() { return CascH.Len(); }
};

#endif
