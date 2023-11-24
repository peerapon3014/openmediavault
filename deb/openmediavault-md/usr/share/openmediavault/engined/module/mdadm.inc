<?php
/**
 * This file is part of OpenMediaVault.
 *
 * @license   http://www.gnu.org/licenses/gpl.html GPL Version 3
 * @author    Volker Theile <volker.theile@openmediavault.org>
 * @copyright Copyright (c) 2009-2023 Volker Theile
 *
 * OpenMediaVault is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * OpenMediaVault is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenMediaVault. If not, see <http://www.gnu.org/licenses/>.
 */
namespace Engined\Module;

class MdAdm extends \OMV\Engine\Module\ServiceAbstract
		implements \OMV\Engine\Notify\IListener, \OMV\Engine\Module\INotification {
	public function getName() {
		return "mdadm";
	}

	public function deployAfter(): array {
		return ["email"];
	}

	public function getNotificationConfig() {
		return [
			[
				"id" => "mdadm",
				"type" => getText("Storage"),
				"title" => gettext("Software RAID")
			]
		];
	}

	function bindListeners(\OMV\Engine\Notify\Dispatcher $dispatcher) {
		$dispatcher->addListener(
			OMV_NOTIFY_CREATE | OMV_NOTIFY_MODIFY | OMV_NOTIFY_DELETE,
			"org.openmediavault.conf.system.mdadm.device",
			[$this, "setDirty"]);
		$dispatcher->addListener(
			OMV_NOTIFY_MODIFY,
			"org.openmediavault.conf.system.notification.email",
			[$this, "setDirty"]);
		$dispatcher->addListener(
			OMV_NOTIFY_CREATE | OMV_NOTIFY_MODIFY,
			"org.openmediavault.conf.system.notification.notification",
			[$this, "setDirty"]);
	}
}