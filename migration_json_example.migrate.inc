<?php
/**
 * @file
 * Declares our migrations.
 *
 * @see: https://www.drupal.org/node/1006982
 */

/**
 * Implements hook_migrate_api().
 */
function migration_json_example_migrate_api() {
  $migrations = array();
  $tasks = array(
    'UserJsonMigration' => array(
      'class_name' => 'UserJsonMigration',
      'description' => 'Migration of users',
    ),
    'ArticleJsonMigration' => array(
      'class_name' => 'ArticleJsonMigration',
      'description' => 'Migration of written articles',
      "user_migration" => 'UserJsonMigration',
    ),
  );

  foreach ($tasks as $name => $args) {
    $migrations[$name] = $args + array(
      'group_name' => MIGRATION_JSON_EXAMPLE_GROUP,
    );
  }
  $api = array(
    'api' => 2,
    'groups' => array(
      MIGRATION_JSON_EXAMPLE_GROUP => array(
        'title' => t('Migrate JSON content'),
      ),
    ),
    'migrations' => $migrations,
  );
  return $api;
}
