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



<start name="encryptor" ram="32M" caps="200">
  <binary name="encryptor"/>
  <provides> <service name="File_system"/> </provides>
  <config>
    <libc stdout="/dev/log" stderr="/dev/log"/>
    <vfs>
      <dir name="dev"> <log/> </dir>
      <dir name="tmp"> <ram/> </dir>
      <dir name="usb_keystorage"> <fatfs/> </dir>
      <!--
      <dir name="snapshot"> <fs/> </dir>
      -->
    </vfs>
  </config>
  <route>
    <service name="Block"> <child name="usb_sec"/> </service>
    <!--
    <service name="File_system"><child name="encryptor"/></service>
    -->
    <any-service> <parent/> </any-service>
  </route>
</start>



<!--
<start name="vfs" ram="200M" caps="200">
  <provides><service name="File_system"/></provides>
  <config>
   	<vfs>
   		<dir name="dev">
   			<block name="block" block_buffer_count="128"/>
   		</dir>
      <lwext4 block_device="/dev/block" cache_write_back="yes"
              expand_via_io="no" writeable="yes"
              reporting="no"
              external_cache_size="32M" report_cache="yes"/>
   	</vfs>
   	<policy label_prefix="snapper" root="/" writeable="yes"/>
  </config>
  <route>
    <service name="Block"> <child name="ahci"/> </service>
    <any-service> <parent/> <any-child/> </any-service>
  </route>
</start>
-->
