/**
 * Copyright 2020 The Magma Authors.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "3gpp_24.008.h"
#include "3gpp_38.401.h"
#include "3gpp_38.413.h"
#include "3gpp_38.331.h"
#include "3gpp_23.003.h"
#include "TrackingAreaIdentity.h"
#include "Ngap_Cause.h"
#include "Ngap_PagingDRX.h"
#include "Ngap_PagingPriority.h"

typedef uint16_t sctp_stream_id_t;
typedef uint32_t sctp_assoc_id_t;
typedef uint64_t gnb_ngap_id_key_t;
typedef uint64_t bitrate_t;

typedef uint8_t DelayValue_t;
typedef uint8_t priority_level_t;
#define PRIORITY_LEVEL_FMT "0x%" PRIu8
#define PRIORITY_LEVEL_SCAN_FMT SCNu8
typedef uint32_t SequenceNumber_t;
typedef uint32_t teid_t;

#define NGAP_GNB_DEREGISTERED_IND(mSGpTR)                                      \
  (mSGpTR)->ittiMsg.ngap_gNB_deregistered_ind
#define NGAP_UE_CONTEXT_RELEASE_REQ(mSGpTR)                                    \
  (mSGpTR)->ittiMsg.ngap_ue_context_release_req
#define NGAP_UE_CONTEXT_RELEASE_COMMAND(mSGpTR)                                \
  (mSGpTR)->ittiMsg.ngap_ue_context_release_command
#define NGAP_UE_CONTEXT_RELEASE_COMPLETE(mSGpTR)                               \
  (mSGpTR)->ittiMsg.ngap_ue_context_release_complete
#define NGAP_UE_CONTEXT_MODIFICATION_REQUEST(mSGpTR)                           \
  (mSGpTR)->ittiMsg.ngap_ue_context_mod_request
#define NGAP_UE_CONTEXT_MODIFICATION_RESPONSE(mSGpTR)                          \
  (mSGpTR)->ittiMsg.ngap_ue_context_mod_response
#define NGAP_UE_CONTEXT_MODIFICATION_FAILURE(mSGpTR)                           \
  (mSGpTR)->ittiMsg.ngap_ue_context_mod_failure

#define NGAP_INITIAL_UE_MESSAGE(mSGpTR)                                        \
  (mSGpTR)->ittiMsg.ngap_initial_ue_message
#define NGAP_NAS_DL_DATA_REQ(mSGpTR) (mSGpTR)->ittiMsg.ngap_nas_dl_data_req
#define NGAP_PAGING_REQUEST(mSGpTR) (mSGpTR)->ittiMsg.ngap_paging_request
#define NGAP_PATH_SWITCH_REQUEST(mSGpTR)                                       \
  (mSGpTR)->ittiMsg.ngap_path_switch_request
#define NGAP_PATH_SWITCH_REQUEST_ACK(mSGpTR)                                   \
  (mSGpTR)->ittiMsg.ngap_path_switch_request_ack
#define NGAP_PATH_SWITCH_REQUEST_FAILURE(mSGpTR)                               \
  (mSGpTR)->ittiMsg.ngap_path_switch_request_failure

#define NGAP_PDUSESSION_RESOURCE_SETUP_REQ(mSGpTR)                             \
  (mSGpTR)->ittiMsg.ngap_pdusession_resource_setup_req
#define NGAP_PDUSESSIONRESOURCE_SETUP_RSP(mSGpTR)                              \
  (mSGpTR)->ittiMsg.ngap_pdusessionresource_setup_rsp
#define NGAP_PDUSESSIONRESOURCE_REL_RSP(mSGpTR)                                \
  (mSGpTR)->ittiMsg.ngap_pdusessionresource_rel_rsp
#define NGAP_PDUSESSIONRESOURCE_REL_REQ(mSGpTR)                                \
  (mSGpTR)->ittiMsg.ngap_pdusessionresource_rel_req

// NOT a ITTI message
typedef struct ngap_initial_ue_message_s {
  gnb_ue_ngap_id_t gnb_ue_ngap_id : 24;
  ecgi_t e_utran_cgi;
} ngap_initial_ue_message_t;

typedef struct itti_ngap_initial_ctxt_setup_req_s {
  amf_ue_ngap_id_t amf_ue_ngap_id;
  gnb_ue_ngap_id_t gnb_ue_ngap_id : 24;

  /* Key gNB */
  uint8_t kgnb[32];

  unsigned ebi : 4;

  /* QoS */
  qci_t qci;
  priority_level_t prio_level;
  teid_t teid;
} itti_ngap_initial_ctxt_setup_req_t;

// List of possible causes for AMF generated UE context release command towards
// gNB
enum Ngcause {
  NGAP_INVALID_CAUSE = 0,
  NGAP_NAS_NORMAL_RELEASE,
  NGAP_NAS_DEREGISTER,
  NGAP_RADIO_NR_GENERATED_REASON,
  NGAP_IMPLICIT_CONTEXT_RELEASE,
  NGAP_INITIAL_CONTEXT_SETUP_FAILED,
  NGAP_SCTP_SHUTDOWN_OR_RESET,
  NGAP_INITIAL_CONTEXT_SETUP_TMR_EXPRD,
  NGAP_INVALID_GNB_ID,
  NGAP_CSFB_TRIGGERED,
  NGAP_NAS_UE_NOT_AVAILABLE_FOR_PS
};
typedef struct itti_ngap_ue_context_release_command_s {
  amf_ue_ngap_id_t amf_ue_ngap_id;
  gnb_ue_ngap_id_t gnb_ue_ngap_id : 24;
  enum Ngcause cause;
} itti_ngap_ue_context_release_command_t;

typedef struct itti_ngap_ue_context_release_req_s {
  amf_ue_ngap_id_t amf_ue_ngap_id;
  gnb_ue_ngap_id_t gnb_ue_ngap_id : 24;
  uint32_t gnb_id;
  enum Ngcause relCause;
  Ngap_Cause_t cause;
} itti_ngap_ue_context_release_req_t;

typedef struct itti_ngap_dl_nas_data_req_s {
  amf_ue_ngap_id_t amf_ue_ngap_id;
  gnb_ue_ngap_id_t gnb_ue_ngap_id : 24;
  bstring nas_msg; /* Downlink NAS message             */
} itti_ngap_nas_dl_data_req_t;

typedef struct itti_ngap_ue_context_release_complete_s {
  amf_ue_ngap_id_t amf_ue_ngap_id;
  gnb_ue_ngap_id_t gnb_ue_ngap_id : 24;
} itti_ngap_ue_context_release_complete_t;

typedef struct itti_ngap_initial_ue_message_s {
  sctp_assoc_id_t sctp_assoc_id;  // key stored in AMF_APP for AMF_APP forward
                                  // NAS response to NGAP
  uint32_t gnb_id;
  gnb_ue_ngap_id_t gnb_ue_ngap_id;
  amf_ue_ngap_id_t amf_ue_ngap_id;
  bstring nas;
  tai_t tai; /* Indicating the Tracking Area from which the UE has sent the NAS
                message. */
  ecgi_t ecgi; /* Indicating the cell from which the UE has sent the NAS
                  message. */
  m5g_rrc_establishment_cause_t
      m5g_rrc_establishment_cause; /* Establishment cause */
  bool is_s_tmsi_valid;
  bool is_csg_id_valid;
  bool is_guamfi_valid;
  s_tmsi_m5_t opt_s_tmsi;
  csg_id_t opt_csg_id;
  guamfi_t opt_guamfi;
  /* Transparent message from ngap to be forwarded to AMF_APP or
   * to NGAP if connection establishment is rejected by NAS.
   */
  ngap_initial_ue_message_t transparent;
} itti_ngap_initial_ue_message_t;

#define NGAP_ITTI_UE_PER_DEREGISTER_MESSAGE 128
typedef struct itti_ngap_gNB_deregistered_ind_s {
  uint16_t nb_ue_to_deregister;
  gnb_ue_ngap_id_t gnb_ue_ngap_id[NGAP_ITTI_UE_PER_DEREGISTER_MESSAGE];
  amf_ue_ngap_id_t amf_ue_ngap_id[NGAP_ITTI_UE_PER_DEREGISTER_MESSAGE];
  uint32_t gnb_id;
} itti_ngap_gNB_deregistered_ind_t;

typedef struct itti_ngap_pdusession_resource_setup_req_s {
  gnb_ue_ngap_id_t gnb_ue_ngap_id;
  amf_ue_ngap_id_t amf_ue_ngap_id;
  bstring nas_pdu;  // optional

  ngap_ue_aggregate_maximum_bit_rate_t
      ue_aggregate_maximum_bit_rate;  // optional

  Ngap_PDUSession_Resource_Setup_Request_List_t pduSessionResource_setup_list;
} itti_ngap_pdusession_resource_setup_req_t;

typedef struct itti_ngap_pdusessionresource_setup_rsp_s {
  amf_ue_ngap_id_t amf_ue_ngap_id;
  gnb_ue_ngap_id_t gnb_ue_ngap_id;

  Ngap_PDUSession_Resource_Setup_Response_List_t pduSessionResource_setup_list;
  Ngap_PDUSession_Resource_Failed_To_Setup_List_t
      pduSessionResourceFailedToSetupList;

} itti_ngap_pdusessionresource_setup_rsp_t;

typedef struct itti_ngap_pdusessionresource_rel_rsp_s {
  amf_ue_ngap_id_t amf_ue_ngap_id;
  gnb_ue_ngap_id_t gnb_ue_ngap_id;

  Ngap_PDUSession_Resource_Released_List_t pduSessionResourceReleasedRspList;

} itti_ngap_pdusessionresource_rel_rsp_t;

typedef struct itti_ngap_pdusessionresource_rel_req_s {
  amf_ue_ngap_id_t amf_ue_ngap_id;
  gnb_ue_ngap_id_t gnb_ue_ngap_id;
  bstring nas_msg;
  Ngap_PDUSession_Resource_TO_Release_List_t pduSessionResourceToRelReqList;

} itti_ngap_pdusessionresource_rel_req_t;

typedef struct itti_ngap_paging_request_s {
  s_tmsi_m5_t UEPagingIdentity;
  e_Ngap_PagingDRX default_paging_drx;  // v32, v64, v128, v256
  e_Ngap_PagingPriority PagingPriority;
  Ngap_TAI_List_For_Paging_t TAIListForPaging;

} itti_ngap_paging_request_t;
