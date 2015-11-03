<?php
/**
 * @file
 * Migration of users.
 */

/**
 * Class JSONMigration.
 *
 * @see:https://www.drupal.org/node/1349632
 */
class UserJsonMigration extends Migration {
  /**
   * {@inheritdoc}
   */
  public function __construct($arguments) {
    parent::__construct($arguments);
    $fields = array(
      'email',
      'first_name',
      'last_name',
      'name',
      'account_id',
    );

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'account_id' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'Unique UID',
        ),
      ),
      MigrateDestinationUser::getKeySchema()
    );

    $reader = array('reader_class' => 'MigrateJSONReader');
    $this->source = new MigrateSourceJSON(MIGRATION_JSON_EXAMPLE_USER_URL, 'account_id', $fields, $reader);
    $options = array(
      'language' => LANGUAGE_NONE,
    );
    $this->destination = new MigrateDestinationUser($options);
    // Map email field.
    $this->addFieldMapping('mail', 'email');
    // Map username field.
    $this->addFieldMapping('name', 'Name')
      ->dedupe('users', 'name');
    // Create a default password.
    $this->addFieldMapping('pass')
      ->defaultValue('passPassword');
    // Add default authenticated role.
    $this->addFieldMapping('roles')
      ->defaultValue(DRUPAL_AUTHENTICATED_RID);
    // Status, lets set them active users.
    $this->addFieldMapping('status')
      ->defaultValue(1);
    // Lets import first and last names, create this field in account settings.
    $this->addFieldMapping('field_first_name', 'first_name');
    $this->addFieldMapping('field_last_name', 'last_name');
  }

}
