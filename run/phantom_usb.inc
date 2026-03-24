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
    <policy label_prefix="encryptor -> usb" root="/" writeable="yes"/>
  </config>
  <route>
   <service name="Block"> <child name="usb_sec"/> </service>
   <any-service> <parent/> <any-child/> </any-service>
  </route>
</start>


<start name="encryptor" ram="32M" caps="200">
  <binary name="encryptor"/>
  <config>
    <libc stdout="/dev/log" stderr="/dev/log"/>
    <vfs>
      <dir name="dev">
        <log/>
      </dir>

      <dir name="mnt">
        <fs label="usb" writeable="yes"/>
      </dir>
    </vfs>
  </config>

  <route>
    <service name="File_system">
      <child name="usb_vfs"/>
    </service>

    <service name="LOG">
      <parent/>
    </service>
    <service name="ROM">
      <parent/>
    </service>
    <service name="CPU">
      <parent/>
    </service>
    <service name="PD">
      <parent/>
    </service>
    <service name="Timer">
      <parent/>
    </service>

    <any-service>
      <parent/>
    </any-service>
  </route>
</start>