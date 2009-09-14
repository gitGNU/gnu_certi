// ----------------------------------------------------------------------------
// CERTI - HLA RunTime Infrastructure
// Copyright (C) 2002, 2003, 2004  ONERA
//
// This file is part of CERTI
//
// CERTI is free software ; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation ; either version 2 of the License, or
// (at your option) any later version.
//
// CERTI is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY ; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program ; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//
// $Id: RTIG.hh,v 3.32 2009/09/14 17:54:09 erk Exp $
// ----------------------------------------------------------------------------

#ifndef CERTI_RTIG_HH
#define CERTI_RTIG_HH

#include "certi.hh"
#include "NetworkMessage.hh"
#include "NM_Classes.hh"
#include "SecureTCPSocket.hh"
#include "SocketServer.hh"
#include "FederationsList.hh"
#include "AuditFile.hh"
#include "HandleManager.hh"

namespace certi {
namespace rtig {

/**
 * This class manages the RTIG server, aka RTI Gateway server.
 * Each time a message is received, it is
 * processed by a RTI_processing.cc module.
 *
 * These modules called "processXXX" are divided into two parts :
 * <ul>
 *   <li> one part for treating the received message. </li>
 *   <li> another part generating and sending back a response. </li>
 * </li>
 */
class RTIG
{
public:
    RTIG();
    ~RTIG();

    static void signalHandler(int sig);
    static bool terminate ;
    void setVerboseLevel(int level) { verboseLevel = level ; federations.setVerboseLevel(level);}
    void execute();


private:
    // Both methods return the socket, because it may have been closed
    // & deleted.
  Socket* processIncomingMessage(Socket*) throw (NetworkError) ;
    Socket* chooseProcessingMethod(Socket*, NetworkMessage *);

    void openConnection();
    void closeConnection(Socket*, bool emergency);

    // Event handlers
    void processCreateFederation(Socket*, NM_Create_Federation_Execution*);
    void processJoinFederation(Socket*, NM_Join_Federation_Execution*);
    void processResignFederation(Socket*,Handle, FederateHandle);
    void processDestroyFederation(Socket*, NM_Destroy_Federation_Execution*);
    void processSetClassRelevanceAdvisorySwitch(Socket*, 
    				NM_Set_Class_Relevance_Advisory_Switch*);
    void processSetInteractionRelevanceAdvisorySwitch(Socket*, 
    				NM_Set_Interaction_Relevance_Advisory_Switch*);
    void processSetAttributeRelevanceAdvisorySwitch(Socket*,
    				NM_Set_Attribute_Relevance_Advisory_Switch*);
    void processSetAttributeScopeAdvisorySwitch(Socket*, 
    				NM_Set_Attribute_Scope_Advisory_Switch*);
    void processSetTimeRegulating(Socket*, NM_Set_Time_Regulating *msg);
    void processSetTimeConstrained(Socket*, NM_Set_Time_Constrained *msg);
    void processMessageNull(NetworkMessage*);
    void processRegisterSynchronization(Socket*, NM_Register_Federation_Synchronization_Point*);
    void processSynchronizationAchieved(Socket*, NetworkMessage*);
    void processRequestFederationSave(Socket*, NetworkMessage*);
    void processFederateSaveBegun(Socket*, NetworkMessage*);
    void processFederateSaveStatus(Socket*, NetworkMessage*);
    void processRequestFederationRestore(Socket*, NetworkMessage*);
    void processFederateRestoreStatus(Socket*, NetworkMessage*);
    void processPublishObjectClass(Socket*, NetworkMessage*);
    void processSubscribeObjectClass(Socket*, NetworkMessage*);
    void processUnpublishObjectClass(Socket*, NetworkMessage*);
    void processUnsubscribeObjectClass(Socket*, NetworkMessage*);
    void processPublishInteractionClass(Socket*, NetworkMessage*);
    void processSubscribeInteractionClass(Socket*, NetworkMessage*);
    void processUnpublishInteractionClass(Socket*, NetworkMessage*);
    void processUnsubscribeInteractionClass(Socket*, NetworkMessage*msg);
    void processRegisterObject(Socket*, NetworkMessage*);
    void processUpdateAttributeValues(Socket*, NetworkMessage*);
    void processSendInteraction(Socket*, NetworkMessage*);
    void processDeleteObject(Socket*, NetworkMessage*);
    void processQueryAttributeOwnership(Socket*, NetworkMessage*);
    void processNegotiatedOwnershipDivestiture(Socket*, NetworkMessage*);
    void processAcquisitionIfAvailable(Socket*, NetworkMessage*);
    void processUnconditionalDivestiture(Socket*, NetworkMessage*);
    void processOwnershipAcquisition(Socket*, NetworkMessage*);
    void processCancelNegotiatedDivestiture(Socket*, NetworkMessage*);
    void processAttributeOwnedByFederate(Socket*, NetworkMessage*);
    void processReleaseResponse(Socket*, NetworkMessage*);
    void processCancelAcquisition(Socket*, NetworkMessage*);
    void processCreateRegion(Socket*, NetworkMessage*);
    void processModifyRegion(Socket*, NetworkMessage*);
    void processDeleteRegion(Socket*, NetworkMessage*);
    void processAssociateRegion(Socket*, NetworkMessage*);
    void processUnassociateRegion(Socket*, NetworkMessage*);
    void processSubscribeAttributesWR(Socket*, NetworkMessage*);
    void processUnsubscribeAttributesWR(Socket*, NetworkMessage*);
    void processSubscribeInteractionWR(Socket*, NetworkMessage*);
    void processUnsubscribeInteractionWR(Socket*, NetworkMessage*);
    void processRegisterObjectWithRegion(Socket*, NetworkMessage*);
    void processRequestObjectAttributeValueUpdate(Socket*, NetworkMessage*);

private:
    int tcpPort ;
    int udpPort ;
    int verboseLevel ;
    HandleManager<Handle> federationHandles ;
    SocketTCP tcpSocketServer ;
    SocketUDP udpSocketServer ;
    SocketServer socketServer ;
    AuditFile auditServer ;
    FederationsList federations ;
    /* The message buffer used to send Network messages */
    MessageBuffer NM_msgBufSend;
    /* The message buffer used to receive Network messages */
    MessageBuffer NM_msgBufReceive;
};

}} // namespaces

#endif // CERTI_RTIG_HH

// $Id: RTIG.hh,v 3.32 2009/09/14 17:54:09 erk Exp $
