<start name="usb_sec" ram="4M">
  <binary name="usb_block"/>
  <provides> <service name="Block"/> </provides>
  <config label="usb_drive" report="yes" writeable="yes" interface="0"
          alt_setting="0" lun="0" reset_device="no" verbose_scsi="no"/>
  <route>
   <service name="Usb"> <child name="usb"/> </service>
   <service name="Report"> <child name="report_rom"/> </service>
   <any-service> <parent/> <any-child/> </any-service>
  </route>
</start>



<!--
<start name="usb_vfs" ram="24M">
  <binary name="vfs"/>
 	<provides><service name="File_system"/></provides>
 	<config>
 		<vfs>
 			<dir name="dev">
 				<block name="usb_block" block_buffer_count="512" service="Block"/>
 			</dir>
			<lwext4 block_device="/dev/usb_block" cache_write_back="yes"
				      expand_via_io="yes" writeable="yes"
				      reporting="yes"
				      external_cache_size="0M" report_cache="no"/>
 		</vfs>
 	</config>
  <route>
   <service name="Block"> <child name="usb_sec"/> </service>
   <any-service> <parent/> <any-child/> </any-service>
  </route>
</start>
-->

<start name="usb_vfs" ram="32M">
  <binary name="vfs"/>
  <provides>
    <service name="File_system"/>
  </provides>
  <config>
    <vfs>
      <fatfs label="usb"
             block_device="/dev/usb_block"
             writeable="yes"/>
    </vfs>
  </config>
  <route>
   <service name="Block"> <child name="usb_sec"/> </service>
   <any-service> <parent/> <any-child/> </any-service>
  </route>
</start>

<start name="encryptor" ram="32M">
    <config/>
    <route>
        <service name="File_system"><child name="usb_vfs"/></service>
        <any-service><parent/></any-service>
    </route>
</start>

