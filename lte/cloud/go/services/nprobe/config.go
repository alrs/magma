/*
Copyright 2020 The Magma Authors.

This source code is licensed under the BSD-style license found in the
LICENSE file in the root directory of this source tree.

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

package nprobe

import (
	"magma/lte/cloud/go/lte"
	"magma/orc8r/lib/go/service/config"

	"github.com/golang/glog"
)

const (
	// DefaultUpdateIntervalSecs is the default periodic time between runs in seconds
	DefaultUpdateIntervalSecs = 60
	// DefaultBackOffIntervalSecs is the default backoff time when remote server is not available
	DefaultBackOffIntervalSecs = 360
)

// Config represents the configuration provided to nprobe service
type Config struct {
	UpdateIntervalSecs  uint `yaml:"update_interval_secs"`
	BackOffIntervalSecs uint `yaml:"backoff_interval_secs"`
}

// GetServiceConfig parses nprobe service config and returns Config
func GetServiceConfig() Config {
	var serviceConfig Config
	_, _, err := config.GetStructuredServiceConfig(lte.ModuleName, ServiceName, &serviceConfig)
	if err != nil {
		glog.Fatalf("Failed parsing nprobe config file: %v ", err)
	}
	if serviceConfig.UpdateIntervalSecs == 0 {
		serviceConfig.UpdateIntervalSecs = DefaultUpdateIntervalSecs
	}
	if serviceConfig.BackOffIntervalSecs == 0 {
		serviceConfig.BackOffIntervalSecs = DefaultBackOffIntervalSecs
	}
	return serviceConfig
}
