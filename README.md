# Import to Drupal 7 JSON (example)

## This example covers
* User migration
* Content migration
* Authoring of content
* Importing pictures declared in JSON file
* Importing creating/terms from JSON file

Basic example that shows how to import JSON data into Drupal 7 using migrate, it contains several files.
The JSON files contain the data to be imported, you can find these files in the *files* folder. They consist of all users and articles,
that will be imported. You can extend/modify this basic example to your needs.
Improvements/suggestions are welcome.

The *inc* folder includes all our custom migrate classes, they extend migrate base class.
They also set the destination class where your content will go to.

In *Migration_json_example.inc* files, contains our hook_migrate_api which will register our migrations with migrate,
so migrate is aware of our code.

To run this example, you will need to have migrate and migrate_ui installed.
Drush en -y migrate migrate_ui

## Getting it working
1. Copy this 2 JSON files, where you can access them via an URL.
2. Update the *migration_json_example.module* file with these URLs.

Enable the module as you would any module in drupal, either via the Interface or drush.
1. drush en -y migration_json_example.

You must run first the users import then the article, you can import them via the migrate interface or via drush:
1. drush mi UserJsonMigration
2. drush mi ArticleJsonMigration

*To rollback on the migration*:
1. drush mr UserJsonMigration
2. drush mr ArticleJsonMigration







